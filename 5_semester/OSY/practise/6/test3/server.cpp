//***************************************************************************
//
// Program example for labs in subject Operating Systems
//
// Petr Olivka, Dept. of Computer Science, petr.olivka@vsb.cz, 2017
//
// Example of socket server.
//
// This program is example of socket server and it allows to connect and serve
// multiple clients using separate processes.
// The mandatory argument of program is port number for listening.
//
//***************************************************************************

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>

#define STR_CLOSE   "close"
#define STR_QUIT    "quit"

//***************************************************************************
// log messages

#define LOG_ERROR               0       // errors
#define LOG_INFO                1       // information and notifications
#define LOG_DEBUG               2       // debug messages

// debug flag
int g_debug = LOG_INFO;

void log_msg( int t_log_level, const char *t_form, ... )
{
    const char *out_fmt[] = {
            "ERR: (%d-%s) %s\n",
            "INF: %s\n",
            "DEB: %s\n" };

    if ( t_log_level && t_log_level > g_debug ) return;

    char l_buf[ 1024 ];
    va_list l_arg;
    va_start( l_arg, t_form );
    vsprintf( l_buf, t_form, l_arg );
    va_end( l_arg );

    switch ( t_log_level )
    {
    case LOG_INFO:
    case LOG_DEBUG:
        fprintf( stdout, out_fmt[ t_log_level ], l_buf );
        break;

    case LOG_ERROR:
        fprintf( stderr, out_fmt[ t_log_level ], errno, strerror( errno ), l_buf );
        break;
    }
}

//***************************************************************************
// help

void help( int t_narg, char **t_args )
{
    if ( t_narg <= 1 || !strcmp( t_args[ 1 ], "-h" ) )
    {
        printf(
            "\n"
            "  Socket server example.\n"
            "\n"
            "  Use: %s [-h -d] port_number\n"
            "\n"
            "    -d  debug mode \n"
            "    -h  this help\n"
            "\n", t_args[ 0 ] );

        exit( 0 );
    }

    if ( !strcmp( t_args[ 1 ], "-d" ) )
        g_debug = LOG_DEBUG;
}

//***************************************************************************
// Signal handler to reap zombie processes
void sigchld_handler(int signo) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

//***************************************************************************

int main( int t_narg, char **t_args )
{
    if ( t_narg <= 1 ) help( t_narg, t_args );

    int l_port = 0;

    // parsing arguments
    for ( int i = 1; i < t_narg; i++ )
    {
        if ( !strcmp( t_args[ i ], "-d" ) )
            g_debug = LOG_DEBUG;

        if ( !strcmp( t_args[ i ], "-h" ) )
            help( t_narg, t_args );

        if ( *t_args[ i ] != '-' && !l_port )
        {
            l_port = atoi( t_args[ i ] );
            break;
        }
    }

    if ( l_port <= 0 )
    {
        log_msg( LOG_INFO, "Bad or missing port number %d!", l_port );
        help( t_narg, t_args );
    }

    log_msg( LOG_INFO, "Server will listen on port: %d.", l_port );

    // socket creation
    int l_sock_listen = socket( AF_INET, SOCK_STREAM, 0 );
    if ( l_sock_listen == -1 )
    {
        log_msg( LOG_ERROR, "Unable to create socket.");
        exit( 1 );
    }

    in_addr l_addr_any = { INADDR_ANY };
    sockaddr_in l_srv_addr;
    l_srv_addr.sin_family = AF_INET;
    l_srv_addr.sin_port = htons( l_port );
    l_srv_addr.sin_addr = l_addr_any;

    // Enable the port number reusing
    int l_opt = 1;
    if ( setsockopt( l_sock_listen, SOL_SOCKET, SO_REUSEADDR, &l_opt, sizeof( l_opt ) ) < 0 )
      log_msg( LOG_ERROR, "Unable to set socket option!" );

    // assign port number to socket
    if ( bind( l_sock_listen, (const sockaddr * ) &l_srv_addr, sizeof( l_srv_addr ) ) < 0 )
    {
        log_msg( LOG_ERROR, "Bind failed!" );
        close( l_sock_listen );
        exit( 1 );
    }

    // listening on set port
    if ( listen( l_sock_listen, 5 ) < 0 ) // Increased backlog for multiple clients
    {
        log_msg( LOG_ERROR, "Unable to listen on given port!" );
        close( l_sock_listen );
        exit( 1 );
    }

    log_msg( LOG_INFO, "Enter 'quit' to quit server." );

    // Set up signal handler for SIGCHLD to prevent zombie processes
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        log_msg( LOG_ERROR, "Failed to set SIGCHLD handler!" );
        exit(1);
    }

    // list of fd sources
    pollfd l_read_poll[2];

    l_read_poll[0].fd = STDIN_FILENO;
    l_read_poll[0].events = POLLIN;
    l_read_poll[1].fd = l_sock_listen;
    l_read_poll[1].events = POLLIN;

    // go!
    while (1)
    {
        // select from fds
        int l_poll = poll( l_read_poll, 2, -1 );

        if ( l_poll < 0 )
        {
            log_msg( LOG_ERROR, "Function poll failed!" );
            continue;
        }

        // data on stdin?
        if ( l_read_poll[0].revents & POLLIN )
        {
            char buf[128];
            int len = read( STDIN_FILENO, buf, sizeof(buf) );
            if ( len < 0 )
            {
                log_msg( LOG_ERROR, "Unable to read from stdin!" );
            }
            else
            {
                buf[len] = '\0'; // Null-terminate the string
                log_msg( LOG_DEBUG, "Read %d bytes from stdin: %s", len, buf );

                // request to quit?
                if ( !strncmp( buf, STR_QUIT, strlen( STR_QUIT ) ) )
                {
                    log_msg( LOG_INFO, "Request to 'quit' entered.");
                    close( l_sock_listen );
                    exit( 0 );
                }
            }
        }

        // data on listening socket?
        if ( l_read_poll[1].revents & POLLIN )
        { // new client?
            sockaddr_in l_rsa;
            socklen_t l_rsa_size = sizeof( l_rsa );
            // new connection
            int l_sock_client = accept( l_sock_listen, ( sockaddr * ) &l_rsa, &l_rsa_size );
            if ( l_sock_client == -1 )
            {
                log_msg( LOG_ERROR, "Unable to accept new client." );
                continue;
            }

            pid_t pid = fork();
            if ( pid < 0 )
            {
                log_msg( LOG_ERROR, "Fork failed!");
                close( l_sock_client );
                continue;
            }

            if ( pid == 0 )
            { // Child process
                close( l_sock_listen ); // Close listening socket in child

                // Log client information
                sockaddr_in l_client_addr;
                socklen_t l_client_len = sizeof(l_client_addr);
                getpeername( l_sock_client, ( sockaddr * ) &l_client_addr, &l_client_len );
                log_msg( LOG_INFO, "Client connected from '%s' port: %d",
                                 inet_ntoa( l_client_addr.sin_addr ), ntohs( l_client_addr.sin_port ) );

                // Read the season request
                char season_buf[32];
                memset(season_buf, 0, sizeof(season_buf));
                int bytes_read = 0;
                int total_read = 0;
                while ((bytes_read = read(l_sock_client, season_buf + total_read, 1)) > 0)
                {
                    if (season_buf[total_read] == '\n') {
                        season_buf[total_read] = '\0'; // Replace '\n' with null terminator
                        break;
                    }
                    total_read += bytes_read;
                    if (total_read >= sizeof(season_buf) - 1)
                        break; // Prevent buffer overflow
                }

                if (bytes_read <= 0)
                {
                    log_msg( LOG_ERROR, "Failed to read season from client." );
                    close( l_sock_client );
                    exit(1);
                }

                log_msg( LOG_INFO, "Client requested season: %s", season_buf );

                // Map season to image file
                char image_path[256];
                if (strcasecmp(season_buf, "jaro") == 0)
                    strcpy(image_path, "images/jaro.jpg");
                else if (strcasecmp(season_buf, "leto") == 0)
                    strcpy(image_path, "images/leto.jpg");
                else if (strcasecmp(season_buf, "podzim") == 0)
                    strcpy(image_path, "images/podzim.jpg");
                else if (strcasecmp(season_buf, "zima") == 0)
                    strcpy(image_path, "images/zima.jpg");
                else
                {
                    log_msg( LOG_ERROR, "Unknown season requested: %s", season_buf );
                    close( l_sock_client );
                    exit(1);
                }

                // Open the image file
                int image_fd = open(image_path, O_RDONLY);
                if (image_fd < 0)
                {
                    log_msg( LOG_ERROR, "Unable to open image file: %s", image_path );
                    close( l_sock_client );
                    exit(1);
                }

                // Send the image in chunks with delays to simulate ~15 seconds
                const int total_delay_ms = 15000; // 15 seconds
                const int chunk_size = 1024; // 1 KB chunks
                char send_buf[chunk_size];
                ssize_t read_bytes;
                while ( (read_bytes = read(image_fd, send_buf, chunk_size)) > 0 )
                {
                    ssize_t sent_bytes = 0;
                    while (sent_bytes < read_bytes)
                    {
                        ssize_t n = write(l_sock_client, send_buf + sent_bytes, read_bytes - sent_bytes);
                        if (n < 0)
                        {
                            log_msg( LOG_ERROR, "Error sending image data to client." );
                            close(image_fd);
                            close(l_sock_client);
                            exit(1);
                        }
                        sent_bytes += n;
                    }
                    // Calculate delay based on chunk size and total image size
                    // For simplicity, sleep a fixed time per chunk
                    usleep( (total_delay_ms * 1000) / (read_bytes > 0 ? read_bytes : 1) ); // Adjust as needed
                }

                close(image_fd);
                log_msg( LOG_INFO, "Image sent to client. Closing connection." );
                close( l_sock_client );
                exit(0);
            }
            else
            { // Parent process
                close( l_sock_client ); // Close client socket in parent
                // Continue to accept new clients
            }
        } // while (1)

    } // main

    return 0;
}