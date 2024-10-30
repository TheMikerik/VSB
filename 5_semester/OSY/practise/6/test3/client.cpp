//***************************************************************************
//
// Program example for subject Operating Systems
//
// Petr Olivka, Dept. of Computer Science, petr.olivka@vsb.cz, 2021
//
// Example of socket server/client.
//
// This program is example of socket client.
// The mandatory arguments of program are IP address or name of server, 
// a port number, and a season request.
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
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/wait.h>

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
            "  Use: %s [-h -d] ip_or_name port_number season\n"
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

int main( int t_narg, char **t_args )
{

    if ( t_narg <= 3 ) help( t_narg, t_args );

    int l_port = 0;
    char *l_host = nullptr;
    char *l_season = nullptr;

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
            else if ( !l_season )
                l_season = t_args[ i ];
        }
    }

    if ( !l_host || !l_port || !l_season )
    {
        log_msg( LOG_INFO, "Host, port, or season is missing!" );
        help( t_narg, t_args );
        exit( 1 );
    }

    log_msg( LOG_INFO, "Connection to '%s':%d.", l_host, l_port );

    addrinfo l_ai_req, *l_ai_ans;
    bzero( &l_ai_req, sizeof( l_ai_req ) );
    l_ai_req.ai_family = AF_INET;
    l_ai_req.ai_socktype = SOCK_STREAM;

    int l_get_ai = getaddrinfo( l_host, nullptr, &l_ai_req, &l_ai_ans );
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

    uint l_lsa = sizeof( l_cl_addr );
    // my IP
    getsockname( l_sock_server, ( sockaddr * ) &l_cl_addr, &l_lsa );
    log_msg( LOG_INFO, "My IP: '%s'  port: %d",
             inet_ntoa( l_cl_addr.sin_addr ), ntohs( l_cl_addr.sin_port ) );
    // server IP
    getpeername( l_sock_server, ( sockaddr * ) &l_cl_addr, &l_lsa );
    log_msg( LOG_INFO, "Server IP: '%s'  port: %d",
             inet_ntoa( l_cl_addr.sin_addr ), ntohs( l_cl_addr.sin_port ) );

    // Send the season request to the server
    size_t season_len = strlen(l_season);
    char season_msg[season_len + 2]; // +1 for '\n' and +1 for '\0'
    snprintf(season_msg, sizeof(season_msg), "%s\n", l_season);

    ssize_t sent = write(l_sock_server, season_msg, strlen(season_msg));
    if (sent < 0)
    {
        log_msg( LOG_ERROR, "Unable to send season to server." );
        close(l_sock_server);
        exit(1);
    }
    else
    {
        log_msg( LOG_DEBUG, "Sent season '%s' to server.", l_season );
    }

    // Prepare to receive image data
    pid_t pid = getpid();
    char filename[64];
    snprintf(filename, sizeof(filename), "%d.img", pid);
    int img_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (img_fd < 0)
    {
        log_msg( LOG_ERROR, "Unable to open file '%s' for writing.", filename );
        close(l_sock_server);
        exit(1);
    }

    // Receive data from server and write to file
    char recv_buf[1024];
    ssize_t recv_len;
    while ( (recv_len = read(l_sock_server, recv_buf, sizeof(recv_buf))) > 0 )
    {
        ssize_t written = 0;
        while (written < recv_len)
        {
            ssize_t w = write(img_fd, recv_buf + written, recv_len - written);
            if (w < 0)
            {
                log_msg( LOG_ERROR, "Unable to write to file '%s'.", filename );
                close(img_fd);
                close(l_sock_server);
                exit(1);
            }
            written += w;
        }
    }

    if (recv_len < 0)
    {
        log_msg( LOG_ERROR, "Error reading data from server." );
        close(img_fd);
        close(l_sock_server);
        exit(1);
    }

    log_msg( LOG_INFO, "Image received and saved to '%s'.", filename );

    close(img_fd);
    close(l_sock_server);

    // Fork to display the image
    pid_t child_pid = fork();
    if (child_pid < 0)
    {
        log_msg( LOG_ERROR, "Fork failed for display process." );
        exit(1);
    }

    if (child_pid == 0)
    { // Child process
        execlp("display", "display", filename, (char *)NULL);
        // If execlp fails
        log_msg( LOG_ERROR, "Failed to execute 'display' command." );
        exit(1);
    }
    else
    { // Parent process
        // Wait for the child to finish
        waitpid(child_pid, NULL, 0);
        log_msg( LOG_INFO, "'display' command completed." );
    }

    return 0;
}