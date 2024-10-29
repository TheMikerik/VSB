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
void handle_client(int client_socket) {
    log_msg(LOG_INFO, "Child process %d handling client.", getpid());

    char buffer[256];
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read < 0) {
            log_msg(LOG_ERROR, "Read error from client.");
            break;
        } else if (bytes_read == 0) {
            log_msg(LOG_INFO, "Client disconnected.");
            break;
        }

        log_msg(LOG_DEBUG, "Received from client: %s", buffer);

        // Ensure the expression ends with '\n'
        if (buffer[bytes_read - 1] != '\n') {
            const char* error_msg = "Error: Expression must end with newline.\n";
            write(client_socket, error_msg, strlen(error_msg));
            continue;
        }

        // Remove the newline character
        buffer[bytes_read - 1] = '\0';

        // Evaluate the expression
        int result;
        if (evaluate_expression(buffer, &result) == 0) {
            char result_str[256];
            snprintf(result_str, sizeof(result_str), "%d\n", result);
            write(client_socket, result_str, strlen(result_str));
            log_msg(LOG_DEBUG, "Sent to client: %s", result_str);
        } else {
            const char* error_msg = "Error: Invalid expression.\n";
            write(client_socket, error_msg, strlen(error_msg));
            log_msg(LOG_DEBUG, "Sent to client: %s", error_msg);
        }
    }

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
        // select from fds
        int l_poll = poll( l_read_poll, 2, -1 );

        if ( l_poll < 0 )
        {
            log_msg( LOG_ERROR, "Function poll failed!" );
            exit( 1 );
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