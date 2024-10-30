//***************************************************************************
//
// Program example for labs in subject Operating Systems
//
// Petr Olivka, Dept. of Computer Science, petr.olivka@vsb.cz, 2017
//
// Example of socket server.
//
// This program is example of socket server and it allows to connect and serve
// the only one client.
// The mandatory argument of program is port number for listening.
//
// Modified by [badadambadadam], 2024
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
#include <signal.h>      // Added for signal handling
#include <ctype.h>       // Added for isspace

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
// Function to evaluate mathematical expressions containing + and -
int evaluate_expression(const char* expr, int* result) {
    int res = 0;
    int sign = 1;
    int num = 0;
    const char* p = expr;

    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        } else if (*p == '+') {
            res += sign * num;
            sign = 1;
            num = 0;
            p++;
        } else if (*p == '-') {
            res += sign * num;
            sign = -1;
            num = 0;
            p++;
        } else if (isdigit(*p)) {
            num = 0;
            while (isdigit(*p)) {
                num = num * 10 + (*p - '0');
                p++;
            }
        } else {
            // Invalid character
            return -1;
        }
    }
    res += sign * num;
    *result = res;
    return 0;
}

//***************************************************************************
// Function to handle each client in a separate process
//***************************************************************************
// Function to handle each client in a separate process
void handle_client(int client_socket) {
    log_msg(LOG_INFO, "Child process %d handling client.", getpid());

    // Buffer to store the received season
    char season_buffer[256];
    memset(season_buffer, 0, sizeof(season_buffer));

    // Read season request from client
    ssize_t bytes_read = 0;
    size_t total_read = 0;
    while ((bytes_read = read(client_socket, season_buffer + total_read, 1)) > 0) {
        if (season_buffer[total_read] == '\n') {
            season_buffer[total_read] = '\0'; // Replace '\n' with null terminator
            break;
        }
        total_read += bytes_read;
        if (total_read >= sizeof(season_buffer) - 1) {
            // Prevent buffer overflow
            log_msg(LOG_ERROR, "Received season name is too long.");
            close(client_socket);
            exit(1);
        }
    }

    if (bytes_read <= 0) {
        log_msg(LOG_ERROR, "Failed to read season from client.");
        close(client_socket);
        exit(1);
    }

    log_msg(LOG_INFO, "Received season request: %s", season_buffer);

    // Map season to corresponding image file
    const char* image_file = nullptr;
    if (strcasecmp(season_buffer, "jaro") == 0) {
        image_file = "spring.png";
    } else if (strcasecmp(season_buffer, "leto") == 0) {
        image_file = "summer.jpg";
    } else if (strcasecmp(season_buffer, "podzim") == 0) {
        image_file = "autumn.jpg";
    } else if (strcasecmp(season_buffer, "zima") == 0) {
        image_file = "winter.png";
    } else if (strcasecmp(season_buffer, "ukonceny") == 0) {
        log_msg(LOG_INFO, "Client requested to close the connection.");
        close(client_socket);
        exit(0);
    } else {
        const char* error_msg = "Error: Invalid season name.\n";
        write(client_socket, error_msg, strlen(error_msg));
        log_msg(LOG_DEBUG, "Sent to client: %s", error_msg);
        close(client_socket);
        exit(1);
    }

    // Check if the image file exists
    if (access(image_file, F_OK) != 0) {
        const char* error_msg = "Error: Image file not found.\n";
        write(client_socket, error_msg, strlen(error_msg));
        log_msg(LOG_DEBUG, "Sent to client: %s", error_msg);
        close(client_socket);
        exit(1);
    }

    // Sleep for approximately 15 seconds
    log_msg(LOG_INFO, "Preparing to send '%s' to client after a delay.", image_file);
    sleep(15);

    // Open the image file
    FILE* img_fp = fopen(image_file, "rb");
    if (!img_fp) {
        const char* error_msg = "Error: Unable to open image file.\n";
        write(client_socket, error_msg, strlen(error_msg));
        log_msg(LOG_ERROR, "Unable to open image file '%s'.", image_file);
        close(client_socket);
        exit(1);
    }

    // Send the image file in chunks
    char send_buffer[1024];
    size_t bytes_sent;
    while ((bytes_sent = fread(send_buffer, 1, sizeof(send_buffer), img_fp)) > 0) {
        ssize_t write_result = write(client_socket, send_buffer, bytes_sent);
        if (write_result <= 0) {
            log_msg(LOG_ERROR, "Failed to send image data to client.");
            break;
        }
    }

    fclose(img_fp);
    log_msg(LOG_INFO, "Finished sending '%s' to client.", image_file);

    // Close the connection
    close(client_socket);
    log_msg(LOG_INFO, "Child process %d exiting.", getpid());
    exit(0);
}

//***************************************************************************
// Signal handler to reap zombie processes
void sigchld_handler(int signo) {
    (void)signo; // Unused parameter
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

//***************************************************************************

int reliable_poll(struct pollfd *fds, nfds_t nfds, int timeout) {
    int ret;
    while (1) {
        ret = poll(fds, nfds, timeout);
        if (ret < 0) {
            if (errno == EINTR) {
                continue; // Retry poll
            } else {
                return -1; // An actual error occurred
            }
        }
        break; // Poll succeeded
    }
    return ret;
}


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
    if ( listen( l_sock_listen, 10 ) < 0 ) // Increased backlog for multiple clients
    {
        log_msg( LOG_ERROR, "Unable to listen on given port!" );
        close( l_sock_listen );
        exit( 1 );
    }

    log_msg( LOG_INFO, "Enter 'quit' to quit server." );

    // Setup signal handler for SIGCHLD to prevent zombie processes
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        log_msg( LOG_ERROR, "Failed to set SIGCHLD handler." );
        exit( 1 );
    }

    // list of fd sources for the parent process
    pollfd l_read_poll[ 2 ];

    l_read_poll[ 0 ].fd = STDIN_FILENO;
    l_read_poll[ 0 ].events = POLLIN;
    l_read_poll[ 1 ].fd = l_sock_listen;
    l_read_poll[ 1 ].events = POLLIN;

    // go!
    while (1)
    {
        int l_poll = reliable_poll(l_read_poll, 2, -1);

        if (l_poll < 0)
        {
            log_msg(LOG_ERROR, "Function poll failed! Errno: %d - %s", errno, strerror(errno));
            exit(1);
        }

        if ( l_read_poll[ 0 ].revents & POLLIN )
        { // data on stdin
            char buf[ 128 ];
            int len = read( STDIN_FILENO, buf, sizeof( buf) );
            if ( len < 0 )
            {
                log_msg( LOG_DEBUG, "Unable to read from stdin!" );
                exit( 1 );
            }

            log_msg( LOG_DEBUG, "Read %d bytes from stdin", len );
            // request to quit?
            if ( !strncmp( buf, STR_QUIT, strlen( STR_QUIT ) ) )
            {
                log_msg( LOG_INFO, "Request to 'quit' entered.");
                close( l_sock_listen );
                exit( 0 );
            }
        }

        if ( l_read_poll[ 1 ].revents & POLLIN )
        { // new client?
            sockaddr_in l_rsa;
            socklen_t l_rsa_size = sizeof( l_rsa );
            // new connection
            int l_sock_client = accept( l_sock_listen, ( sockaddr * ) &l_rsa, &l_rsa_size );
            if ( l_sock_client == -1 )
            {
                log_msg( LOG_ERROR, "Unable to accept new client." );
                continue; // Continue accepting other clients
            }

            pid_t pid = fork();
            if (pid < 0) {
                log_msg( LOG_ERROR, "Fork failed.");
                close(l_sock_client);
                continue;
            }

            if (pid == 0) {
                // Child process
                close(l_sock_listen); // Close listening socket in child
                handle_client(l_sock_client); // This function will exit the child
            } else {
                // Parent process
                close(l_sock_client); // Close client socket in parent
                // Parent continues to accept new clients
            }
        }

    } // while (1)

    return 0;
}