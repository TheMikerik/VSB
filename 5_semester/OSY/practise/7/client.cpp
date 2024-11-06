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
#include <netdb.h>
#include <errno.h>
#include <sys/wait.h>

#define STR_CLOSE               "close"

//***************************************************************************
// log messages

#define LOG_ERROR               0       // errors
#define LOG_INFO                1       // information and notifications
#define LOG_DEBUG               2       // debug messages

// debug flag
int g_debug = LOG_INFO;

//***************************************************************************
// Function to log messages

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
// Function to display help

void help( int t_narg, char **t_args )
{
    if ( t_narg <= 2 || !strcmp( t_args[ 1 ], "-h" ) )
    {
        printf(
            "\n"
            "  Socket client example.\n"
            "\n"
            "  Use: %s [-h -d] ip_or_name port_number season\n"
            "\n"
            "    -d  debug mode \n"
            "    -h  this help\n"
            "    season\n"
            "\n", t_args[ 0 ] );

        exit( 0 );
    }

    if ( !strcmp( t_args[ 1 ], "-d" ) )
        g_debug = LOG_DEBUG;
}

//***************************************************************************

int main( int t_narg, char **t_args )
{
    if ( t_narg <= 3 ) help( t_narg, t_args );

    int l_port = 0;
    char *l_host = nullptr;
    char *season = nullptr;

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
            else if ( !season )
                season = t_args[ i ];
        }
    }

    if ( !l_host || !l_port || !season )
    {
        log_msg( LOG_INFO, "Host, port, or season is missing!" );
        help( t_narg, t_args );
        exit( 1 );
    }

    log_msg( LOG_INFO, "Connection to '%s':%d. Season: %s", l_host, l_port, season );

    addrinfo l_ai_req, *l_ai_ans;
    memset( &l_ai_req, 0, sizeof( l_ai_req ) );
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

    // Socket creation
    int l_sock_server = socket( AF_INET, SOCK_STREAM, 0 );
    if ( l_sock_server == -1 )
    {
        log_msg( LOG_ERROR, "Unable to create socket.");
        exit( 1 );
    }

    // connect to server
    if ( connect( l_sock_server, ( sockaddr * ) &l_cl_addr, sizeof( l_cl_addr ) ) < 0 )
    {
        log_msg( LOG_ERROR, "Unable to connect to server." );
        exit( 1 );
    }

    uint l_lsa = sizeof( l_cl_addr );
    // my IP
    getsockname( l_sock_server, ( sockaddr * ) &l_cl_addr, &l_lsa );
    log_msg( LOG_INFO, "My IP: '%s'  port: %d",
             inet_ntoa( l_cl_addr.sin_addr ), ntohs( l_cl_addr.sin_port ) );
    // server IP
    getpeername( l_sock_server, ( sockaddr * ) &l_cl_addr, &l_lsa );
    log_msg( LOG_INFO, "Server IP: '%s'  port: %d",
             inet_ntoa( l_cl_addr.sin_addr ), ntohs( l_cl_addr.sin_port ) );


    char request[128];
    snprintf(request, sizeof(request), "%s\n", season);
    log_msg( LOG_INFO, "Sending season request: %s", season );


    ssize_t len = write( l_sock_server, request, strlen(request) );
    if ( len < 0 )
    {
        log_msg( LOG_ERROR, "Unable to send data to server." );
        close(l_sock_server);
        exit( 1 );
    }
    log_msg( LOG_DEBUG, "Sent %zd bytes to server.", len );

    pid_t pid = getpid();
    char filename[256];
    snprintf(filename, sizeof(filename), "%d.img", pid);

    int output_file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (output_file < 0)
    {
        log_msg(LOG_ERROR, "Unable to create file: %s", filename);
        close(l_sock_server);
        exit(1);
    }

    log_msg(LOG_INFO, "Receiving image data and saving to %s", filename );

    
    char buffer[2048];
    ssize_t bytes_received;
    while ((bytes_received = read(l_sock_server, buffer, sizeof(buffer))) > 0)
    {
        ssize_t bytes_written = write(output_file, buffer, bytes_received);
        if (bytes_written < 0)
        {
            log_msg(LOG_ERROR, "Unable to write to file: %s", filename);
            close(output_file);
            close(l_sock_server);
            exit(1);
        }
        log_msg(LOG_DEBUG, "Bytes recieved: %zd", bytes_received);
    }

    if (bytes_received < 0)
    {
        log_msg(LOG_ERROR, "Error reading data from server.");
        close(output_file);
        close(l_sock_server);
        exit(1);
    }

    log_msg(LOG_INFO, "Image received successfully.");

    close(output_file);
    close(l_sock_server);


    pid_t child_pid = fork();
    if (child_pid < 0)
    {
        log_msg(LOG_ERROR, "Fork failed.");
        exit(1);
    }
    else if (child_pid == 0)
    {
        execlp("display", "display", filename, (char *)NULL);
        exit(1);
    }
    else
    {
        int status;
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status))
        {
            log_msg(LOG_INFO, "'display' command exited with status %d.", WEXITSTATUS(status));
        }
        else
        {
            log_msg(LOG_INFO, "'display' command terminated abnormally.");
        }
    }

    return 0;
}