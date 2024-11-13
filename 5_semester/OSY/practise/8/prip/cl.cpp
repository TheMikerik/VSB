//***************************************************************************
//
// Program example for subject Operating Systems
//
// Petr Olivka, Dept. of Computer Science, petr.olivka@vsb.cz, 2021
//
// Example of socket server/client.
//
// This program is example of socket client.
// The mandatory arguments of program are IP address or name of server, port number,
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
#include <pthread.h>
#include <string>
#include <algorithm>

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
            "DEB: %s\n"};

    if ( t_log_level && t_log_level > g_debug ) return;

    char l_buf[ 1024 ];
    va_list l_arg;
    va_start( l_arg, t_form );
    vsnprintf( l_buf, sizeof(l_buf), t_form, l_arg );
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
    if ( t_narg <= 3 || !strcmp( t_args[ 1 ], "-h" ) )
    {
        printf(
            "\n"
            "  Socket client example.\n"
            "\n"
            "  Use: %s [-h -d] ip_or_name port_number name\n"
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

void* receive_thread(void* arg){
    int sock = *((int*)arg);
    char buffer[1024];
    while(1){
        ssize_t bytes_received = read(sock, buffer, sizeof(buffer)-1);
        if(bytes_received <= 0){
            if(bytes_received < 0){
                log_msg(LOG_ERROR, "Error reading from server.");
            }
            else{
                log_msg(LOG_INFO, "Server disconnected.");
            }
            close(sock);
            exit(0);
        }
        buffer[bytes_received] = '\0';
        log_msg(LOG_INFO, "[CHAT] %s", buffer);
    }
    return NULL;
}

//***************************************************************************



//***************************************************************************

int main( int t_narg, char **t_args )
{
    if ( t_narg <= 3 ) help( t_narg, t_args );

    int l_port = 0;
    char *l_host = nullptr;
    std::string l_name;

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
            else if ( l_name.empty() )
                l_name = t_args[ i ];
        }
    }

    if ( !l_host || !l_port || l_name.empty() )
    {
        log_msg( LOG_INFO, "Host, port or name is missing!" );
        log_msg( LOG_INFO, "The client has not been created!" );
        help( t_narg, t_args );
        exit( 1 );
    }

    log_msg(LOG_INFO, "-------------CLIENT: #%s-------------", l_name.c_str());
    log_msg(LOG_INFO, "Connected to '%s' on port %d.", l_host, l_port);

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

    log_msg(LOG_INFO, "---------------------------------------\n");

    std::string nick_message = l_name;
    ssize_t nick_len = write(l_sock_server, nick_message.c_str(), nick_message.size());
    if(nick_len < 0){
        log_msg(LOG_ERROR, "Unable to send nickname to server.");
        close(l_sock_server);
        exit(1);
    }
    log_msg(LOG_DEBUG, "Sent nickname to server.");

    pthread_t recv_thread;
    if(pthread_create(&recv_thread, NULL, receive_thread, &l_sock_server) != 0){
        log_msg(LOG_ERROR, "Failed to create receive thread.");
        close(l_sock_server);
        exit(1);
    }

    char input[256];
    while(1){
        if(fgets(input, sizeof(input), stdin) == NULL){
            log_msg(LOG_INFO, "Input closed.");
            break;
        }

        std::string message(input);
        message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
        message += "\n";

        ssize_t len = write(l_sock_server, message.c_str(), message.size());
        if(len < 0){
            log_msg(LOG_ERROR, "Unable to send data to server.");
            break;
        }
        log_msg(LOG_DEBUG, "Sent %zd bytes to server.", len);
    }

    close(l_sock_server);
    return 0;
}