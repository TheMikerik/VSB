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
//***************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
#include <pthread.h>
#include <vector>
#include <map>
#include <string>
#include <semaphore.h>

#define STR_CLOSE    "close"
#define STR_QUIT     "quit"

//***************************************************************************
// log messages

#define LOG_ERROR               0       // errors
#define LOG_INFO                1       // information and notifications
#define LOG_DEBUG               2       // debug messages
#define SEM_BUFFER              10     

// debug flag
int g_debug = LOG_INFO;

sem_t g_mutex;
sem_t g_empty;
sem_t g_full;
std::vector<std::string> g_buffer(SEM_BUFFER);
size_t g_in_index = 0;
size_t g_out_index = 0;

struct ClientData
{
    int sock;
    std::string task;
};

std::vector<int> g_client_sockets;
std::map<int, std::string> g_client_tasks; 

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
void broadcast_to_all( const char* t_buf, int t_len, int t_sender_socket = -1 )
{
    std::string l_message;
    
    if ( t_sender_socket >= 0 && g_client_tasks.find( t_sender_socket ) != g_client_tasks.end() )
    {
        l_message = g_client_tasks[ t_sender_socket ] + ": " + std::string( t_buf, t_len );
    }
    else
    {
        l_message = "SERVER: " + std::string( t_buf, t_len );
    }
    
    log_msg( LOG_DEBUG, "Broadcasting %lu bytes to %lu clients: %s", 
             l_message.length(), g_client_sockets.size(), l_message.c_str() );
    
    write( STDOUT_FILENO, l_message.c_str(), l_message.length() );
    
    for ( size_t i = 0; i < g_client_sockets.size(); i++ )
    {
        int l_written = write( g_client_sockets[ i ], l_message.c_str(), l_message.length() );
        if ( l_written < 0 )
        {
            log_msg( LOG_ERROR, "Unable to send to client socket %d.", g_client_sockets[ i ] );
        }
        else
        {
            log_msg( LOG_DEBUG, "Sent %d bytes to client socket %d.", l_written, g_client_sockets[ i ] );
        }
    }
}

void handle_behavior( const char* t_buf, int t_len, int t_sender_socket, std::string t_task)
{
    std::string data(t_buf, t_len);
    if (!data.empty() && data.back() == '\n')
        data.pop_back();

    if (t_task == "producer")
    {
        sem_wait(&g_empty);
        sem_wait(&g_mutex);

        g_buffer[g_in_index] = data;
        g_in_index = (g_in_index + 1) % SEM_BUFFER;

        sem_post(&g_mutex);
        sem_post(&g_full);

        const char* ok = "OK\n";
        write(t_sender_socket, ok, strlen(ok));
    }
    else if (t_task == "consumer")
    {
        // vyžaduj ACK “OK” od klienta; skutečný požadavek je prázdný read
        if (data == "OK")
        {
            return; // jen potvrzení
        }

        sem_wait(&g_full);
        sem_wait(&g_mutex);

        std::string item = g_buffer[g_out_index];
        g_out_index = (g_out_index + 1) % SEM_BUFFER;

        sem_post(&g_mutex);
        sem_post(&g_empty);

        item.push_back('\n');
        write(t_sender_socket, item.c_str(), item.size());
    }
}

void* handle_client( void* t_arg ){
    ClientData* l_data = (ClientData*)t_arg;

    int l_sock_client = l_data->sock;
    std::string l_task = l_data->task;
    delete (int*)t_arg;

    g_client_sockets.push_back( l_sock_client );
    g_client_tasks[ l_sock_client ] = l_task;
    log_msg( LOG_INFO, "Client socket %d registered with task: '%s'", l_sock_client, l_task.c_str() );

    char l_buf[256];
    
    while ( 1 )
    {
        // read data from client
        int l_len = read( l_sock_client, l_buf, sizeof( l_buf ) - 1 );
        
        if ( l_len == 0 )
        {
            log_msg( LOG_DEBUG, "Client closed socket!" );
            close( l_sock_client );
            break;
        }
        else if ( l_len < 0 )
        {
            log_msg( LOG_ERROR, "Unable to read data from client." );
            close( l_sock_client );
            break;
        }
        else
        {
            l_buf[ l_len ] = '\0';  // null-terminate for string operations
            log_msg( LOG_DEBUG, "Read %d bytes from client.", l_len );
        }
        
        // broadcast_to_all( l_buf, l_len, l_sock_client );
        handle_behavior( l_buf, l_len, l_sock_client, l_task );

        // close request?
        if ( !strncasecmp( l_buf, STR_CLOSE, strlen( STR_CLOSE ) ) )
        {
            log_msg( LOG_INFO, "Client sent 'close' request to close connection." );
            close( l_sock_client );
            log_msg( LOG_INFO, "Connection closed." );
            break;
        }
    }

    for ( size_t i = 0; i < g_client_sockets.size(); i++ )
    {
        if ( g_client_sockets[ i ] == l_sock_client )
        {
            g_client_sockets.erase( g_client_sockets.begin() + i );
            log_msg( LOG_INFO, "Client socket %d removed from list. Remaining clients: %lu", 
                     l_sock_client, g_client_sockets.size() );
            break;
        }
    }
    g_client_tasks.erase( l_sock_client );

    log_msg( LOG_DEBUG, "Thread terminating." );
    pthread_exit( NULL );
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

    if ( l_port % 2 != 0 )
    {
        log_msg( LOG_INFO, "Server port has to be even!", l_port );
        exit( 1 );
    }

    log_msg( LOG_INFO, "Server will listen on ports: %d. and %d", l_port, l_port + 1 );

    // socket creation
    int l_sock_listen_prod = socket( AF_INET, SOCK_STREAM, 0 );
    if ( l_sock_listen_prod == -1 )
    {
        log_msg( LOG_ERROR, "Unable to create socket.");
        exit( 1 );
    }

    int l_sock_listen_cons = socket( AF_INET, SOCK_STREAM, 0 );
    if ( l_sock_listen_cons == -1 )
    {
        log_msg( LOG_ERROR, "Unable to create socket.");
        exit( 1 );
    }

    in_addr l_addr_any = { INADDR_ANY };

    sockaddr_in l_srv_addr_prod;
    l_srv_addr_prod.sin_family = AF_INET;
    l_srv_addr_prod.sin_port = htons( l_port );
    l_srv_addr_prod.sin_addr = l_addr_any;

    sockaddr_in l_srv_addr_cons;
    l_srv_addr_cons.sin_family = AF_INET;
    l_srv_addr_cons.sin_port = htons( l_port + 1 );
    l_srv_addr_cons.sin_addr = l_addr_any;

    // Enable the port number reusing
    int l_opt = 1;
    if ( setsockopt( l_sock_listen_prod, SOL_SOCKET, SO_REUSEADDR, &l_opt, sizeof( l_opt ) ) < 0 )
      log_msg( LOG_ERROR, "Unable to set socket option!" );

    if ( setsockopt( l_sock_listen_cons, SOL_SOCKET, SO_REUSEADDR, &l_opt, sizeof( l_opt ) ) < 0 )
      log_msg( LOG_ERROR, "Unable to set socket option!" );

    // assign port number to socket
    if ( bind( l_sock_listen_prod, (const sockaddr * ) &l_srv_addr_prod, sizeof( l_srv_addr_prod ) ) < 0 )
    {
        log_msg( LOG_ERROR, "Bind failed!" );
        close( l_sock_listen_prod );
        exit( 1 );
    }
    if ( bind( l_sock_listen_cons, (const sockaddr * ) &l_srv_addr_cons, sizeof( l_srv_addr_cons ) ) < 0 )
    {
        log_msg( LOG_ERROR, "Bind failed!" );
        close( l_sock_listen_cons );
        exit( 1 );
    }

    // listenig on set port
    if ( listen( l_sock_listen_prod, 1 ) < 0 )
    {
        log_msg( LOG_ERROR, "Unable to listen on given port!" );
        close( l_sock_listen_prod );
        exit( 1 );
    }

    if ( listen( l_sock_listen_cons, 1 ) < 0 )
    {
        log_msg( LOG_ERROR, "Unable to listen on given port!" );
        close( l_sock_listen_cons );
        exit( 1 );
    }

    log_msg( LOG_INFO, "Enter 'quit' to quit server." );

    sem_init(&g_mutex, 0, 1);
    sem_init(&g_empty, 0, SEM_BUFFER);
    sem_init(&g_full, 0, 0);

    // go!
    while ( 1 )
    {
        // list of fd sources
        pollfd l_read_poll[ 3 ];

        // Sledujeme listen socked a klavesnici
        l_read_poll[ 0 ].fd = STDIN_FILENO;
        l_read_poll[ 0 ].events = POLLIN;
        l_read_poll[ 1 ].fd = l_sock_listen_prod;
        l_read_poll[ 1 ].events = POLLIN;
        l_read_poll[ 2 ].fd = l_sock_listen_cons;
        l_read_poll[ 2 ].events = POLLIN;

        // select from fds
        int l_poll = poll( l_read_poll, 3, -1 );

        if ( l_poll < 0 )
        {
            log_msg( LOG_ERROR, "Function poll failed!" );
            exit( 1 );
        }

        if ( l_read_poll[ 0 ].revents & POLLIN )
        { // data on stdin
            char buf[ 128 ];
            
            int l_len = read( STDIN_FILENO, buf, sizeof( buf) );
            if ( l_len == 0 )
            {
                log_msg( LOG_DEBUG, "Stdin closed." );
                break;
            }
            if ( l_len < 0 )
            {
                log_msg( LOG_ERROR, "Unable to read from stdin!" );
                break;
            }

            log_msg( LOG_DEBUG, "Read %d bytes from stdin", l_len );
            // request to quit?
            if ( !strncmp( buf, STR_QUIT, strlen( STR_QUIT ) ) )
            {
                log_msg( LOG_INFO, "Request to 'quit' entered.");
                close( l_sock_listen_prod );
                close( l_sock_listen_cons );
                exit( 0 );
            }

            if ( l_len > 0 ){
                broadcast_to_all( buf, l_len, -1 );
            }
        }

        if ( l_read_poll[ 1 ].revents & POLLIN )
        { // new client?
            sockaddr_in l_rsa;
            int l_rsa_size = sizeof( l_rsa );
            // new connection
            int l_sock_client = accept( l_sock_listen_prod, ( sockaddr * ) &l_rsa, ( socklen_t * ) &l_rsa_size );
            if ( l_sock_client == -1 )
            {
                log_msg( LOG_ERROR, "Unable to accept new client." );
                continue;
            }
            uint l_lsa = sizeof( l_srv_addr_prod );
            // my IP
            getsockname( l_sock_client, ( sockaddr * ) &l_srv_addr_prod, &l_lsa );
            log_msg( LOG_INFO, "My IP: '%s'  port: %d",
                                inet_ntoa( l_srv_addr_prod.sin_addr ), ntohs( l_srv_addr_prod.sin_port ) );
            // client IP
            getpeername( l_sock_client, ( sockaddr * ) &l_srv_addr_prod, &l_lsa );
            log_msg( LOG_INFO, "Client IP: '%s'  port: %d",
                                inet_ntoa( l_srv_addr_prod.sin_addr ), ntohs( l_srv_addr_prod.sin_port ) );

            ClientData* l_data = new ClientData();
            l_data->sock = l_sock_client;
            l_data->task = "producer";
            
            pthread_t l_thread;
            int l_result = pthread_create(&l_thread, NULL, handle_client, (void*)l_data);
            if ( l_result != 0 ){
                log_msg( LOG_ERROR, "Unable to create thread!" );
                close( l_sock_client );
                delete l_data;
                continue;
            }
            pthread_detach( l_thread );
        }

        if ( l_read_poll[ 2 ].revents & POLLIN )
        { // new client?
            sockaddr_in l_rsa;
            int l_rsa_size = sizeof( l_rsa );
            // new connection
            int l_sock_client = accept( l_sock_listen_cons, ( sockaddr * ) &l_rsa, ( socklen_t * ) &l_rsa_size );
            if ( l_sock_client == -1 )
            {
                log_msg( LOG_ERROR, "Unable to accept new client." );
                continue;
            }
            uint l_lsa = sizeof( l_srv_addr_cons );
            // my IP
            getsockname( l_sock_client, ( sockaddr * ) &l_srv_addr_cons, &l_lsa );
            log_msg( LOG_INFO, "My IP: '%s'  port: %d",
                                inet_ntoa( l_srv_addr_cons.sin_addr ), ntohs( l_srv_addr_cons.sin_port ) );
            // client IP
            getpeername( l_sock_client, ( sockaddr * ) &l_srv_addr_cons, &l_lsa );
            log_msg( LOG_INFO, "Client IP: '%s'  port: %d",
                                inet_ntoa( l_srv_addr_cons.sin_addr ), ntohs( l_srv_addr_cons.sin_port ) );

            ClientData* l_data = new ClientData();
            l_data->sock = l_sock_client;
            l_data->task = "consumer";
            
            pthread_t l_thread;
            int l_result = pthread_create(&l_thread, NULL, handle_client, (void*)l_data);
            if ( l_result != 0 ){
                log_msg( LOG_ERROR, "Unable to create thread!" );
                close( l_sock_client );
                delete l_data;
                continue;
            }
            pthread_detach( l_thread );
        }
    }

    close( l_sock_listen_prod );
    close( l_sock_listen_cons );

    sem_destroy(&g_mutex);
    sem_destroy(&g_empty);
    sem_destroy(&g_full);

    return 0;
}