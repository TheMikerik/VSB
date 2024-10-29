//***************************************************************************
//
// Program example for subject Operating Systems
//
// Petr Olivka, Dept. of Computer Science, petr.olivka@vsb.cz, 2021
//
// Example of socket server/client.
//
// This program is example of socket client.
// The mandatory arguments of program is IP adress or name of server and
// a port number.
//
// Modified by [Your Name], 2024
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
#include <netdb.h>
#include <time.h>        // Added for random expression generation

#define STR_CLOSE               "close"

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
            "  Socket client example.\n"
            "\n"
            "  Use: %s [-h -d] ip_or_name port_number\n"
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
// Function to generate a random mathematical expression with + and -
void generate_random_expression(char* expr, size_t max_len) {
    int num_terms = rand() % 5 + 2; // Between 2 and 6 terms
    int current_len = 0;

    for (int i = 0; i < num_terms; i++) {
        if (current_len >= max_len - 10) break; // Prevent buffer overflow

        int number = rand() % 100; // Random number between 0 and 99
        char op = (i == 0) ? '\0' : (rand() % 2 ? '+' : '-');
        if (op != '\0') {
            current_len += snprintf(expr + current_len, max_len - current_len, " %c ", op);
        }
        current_len += snprintf(expr + current_len, max_len - current_len, "%d", number);
    }
    snprintf(expr + current_len, max_len - current_len, "\n"); // Add newline at the end
}

//***************************************************************************

int main( int t_narg, char **t_args )
{

    if ( t_narg <= 2 ) help( t_narg, t_args );

    int l_port = 0;
    char *l_host = nullptr;

    // parsing arguments
    for ( int i = 1; i < t_narg; i++ )
    {
        if ( !strcmp( t_args[ i ], "-d" ) )
            g_debug = LOG_DEBUG;

        if ( !strcmp( t_args[ i ], "-h" ) )
            help( t_narg, t_args );

        if ( *t_args[ i ] != '-' )
        {
            if ( !l_host )
                l_host = t_args[ i ];
            else if ( !l_port )
                l_port = atoi( t_args[ i ] );
        }
    }

    if ( !l_host || !l_port )
    {
        log_msg( LOG_INFO, "Host or port is missing!" );
        help( t_narg, t_args );
        exit( 1 );
    }

    log_msg( LOG_INFO, "Connection to '%s':%d.", l_host, l_port );

    addrinfo l_ai_req, *l_ai_ans;
    bzero( &l_ai_req, sizeof( l_ai_req ) );
    l_ai_req.ai_family = AF_INET;
    l_ai_req.ai_socktype = SOCK_STREAM;

    int l_get_ai = getaddrinfo( l_host, NULL, &l_ai_req, &l_ai_ans );
    if ( l_get_ai )
    {
        log_msg( LOG_ERROR, "Unknown host name!" );
        exit( 1 );
    }

    sockaddr_in l_cl_addr =  *( sockaddr_in * ) l_ai_ans->ai_addr;
    l_cl_addr.sin_port = htons( l_port );
    freeaddrinfo( l_ai_ans );

    // socket creation
    int l_sock_server = socket( AF_INET, SOCK_STREAM, 0 );
    if ( l_sock_server == -1 )
    {
        log_msg( LOG_ERROR, "Unable to create socket.");
        exit( 1 );
    }

    // connect to server
    if ( connect( l_sock_server, ( sockaddr * ) &l_cl_addr, sizeof( l_cl_addr ) ) < 0 )
    {
        log_msg( LOG_ERROR, "Unable to connect server." );
        exit( 1 );
    }

    socklen_t l_lsa = sizeof( l_cl_addr );
    // my IP
    getsockname( l_sock_server, ( sockaddr * ) &l_cl_addr, &l_lsa );
    log_msg( LOG_INFO, "My IP: '%s'  port: %d",
             inet_ntoa( l_cl_addr.sin_addr ), ntohs( l_cl_addr.sin_port ) );
    // server IP
    getpeername( l_sock_server, ( sockaddr * ) &l_cl_addr, &l_lsa );
    log_msg( LOG_INFO, "Server IP: '%s'  port: %d",
             inet_ntoa( l_cl_addr.sin_addr ), ntohs( l_cl_addr.sin_port ) );

    log_msg( LOG_INFO, "Enter 'close' to close application." );

    // Initialize random number generator
    srand(time(NULL));

    // list of fd sources
    pollfd l_read_poll[ 2 ];

    l_read_poll[0].fd = STDIN_FILENO;
    l_read_poll[0].events = POLLIN;
    l_read_poll[1].fd = l_sock_server;
    l_read_poll[1].events = POLLIN;

    // go!
    while ( 1 )
    {
        // Set timeout to 15000 ms (15 seconds)
        int timeout = 15000; // milliseconds

        int poll_result = poll( l_read_poll, 2, timeout );

        if ( poll_result < 0 ) {
            log_msg( LOG_ERROR, "Poll failed." );
            break;
        } else if ( poll_result == 0 ) {
            // Timeout occurred, generate and send random expression
            char expr[128];
            generate_random_expression(expr, sizeof(expr));
            log_msg( LOG_INFO, "No input detected. Sending random expression: %s", expr);
            ssize_t bytes_sent = write( l_sock_server, expr, strlen(expr) );
            if ( bytes_sent < 0 )
                log_msg( LOG_ERROR, "Unable to send data to server." );
            else
                log_msg( LOG_DEBUG, "Sent %ld bytes to server.", bytes_sent );
            continue; // Continue to next poll
        }

        // data on stdin?
        if ( l_read_poll[0].revents & POLLIN )
        {
            //  read from stdin
            char l_buf[128];
            int l_len = read( STDIN_FILENO, l_buf, sizeof( l_buf ) );
            if ( l_len < 0 )
                log_msg( LOG_ERROR, "Unable to read from stdin." );
            else
                log_msg( LOG_DEBUG, "Read %d bytes from stdin.", l_len );

            // send data to server
            l_len = write( l_sock_server, l_buf, l_len );
            if ( l_len < 0 )
                log_msg( LOG_ERROR, "Unable to send data to server." );
            else
                log_msg( LOG_DEBUG, "Sent %d bytes to server.", l_len );
        }

        // data from server?
        if ( l_read_poll[1].revents & POLLIN )
        {
            // read data from server
            char l_buf[128];
            int l_len = read( l_sock_server, l_buf, sizeof( l_buf ) );
            if ( !l_len )
            {
                log_msg( LOG_DEBUG, "Server closed socket." );
                break;
            }
            else if ( l_len < 0 )
            {
                log_msg( LOG_ERROR, "Unable to read data from server." );
                break;
            }
            else
                log_msg( LOG_DEBUG, "Read %d bytes from server.", l_len );

            // display on stdout
            l_len = write( STDOUT_FILENO, l_buf, l_len );
            if ( l_len < 0 )
                log_msg( LOG_ERROR, "Unable to write to stdout." );

            // request to close?
            if ( !strncasecmp( l_buf, STR_CLOSE, strlen( STR_CLOSE ) ) )
            {
                log_msg( LOG_INFO, "Connection will be closed..." );
                break;
            }
        }
    }

    // close socket
    close( l_sock_server );

    return 0;
}