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
#include <netdb.h>
#include <string>
#include <vector>
#include <fstream>
#include <pthread.h>

#define STR_CLOSE               "close"
#define STR_PRODUCER            "producer"
#define STR_CONSUMER            "consumer"

//***************************************************************************
// log messages

#define LOG_ERROR               0       // errors
#define LOG_INFO                1       // information and notifications
#define LOG_DEBUG               2       // debug messages

// debug flag
int g_debug = LOG_INFO;

int g_names_per_minute = 60;

struct ProducerData
{
    int sock;
    std::vector<std::string> names;
};

struct ConsumerData
{
    int sock;
};

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

std::vector<std::string> load_names( const char* t_filename )
{
    std::vector<std::string> l_names;
    std::ifstream l_file( t_filename );
    
    if ( !l_file.is_open() )
    {
        log_msg( LOG_ERROR, "Unable to open file: %s", t_filename );
        return l_names;
    }
    
    std::string l_line;
    while ( std::getline( l_file, l_line ) )
    {
        if ( !l_line.empty() )
        {
            l_names.push_back( l_line );
        }
    }
    
    l_file.close();
    
    return l_names;
}

void* consumer_thread( void* t_arg )
{
    ConsumerData* l_data = (ConsumerData*)t_arg;
    int l_sock = l_data->sock;
    delete l_data;
    
    log_msg( LOG_INFO, "Consumer thread started. Waiting for names..." );
    
    while ( 1 )
    {
        const char* l_request = "\n";
        int l_len = write( l_sock, l_request, strlen( l_request ) );
        if ( l_len < 0 )
        {
            log_msg( LOG_ERROR, "Unable to send request to server." );
            break;
        }
        log_msg( LOG_DEBUG, "Sent request for item to server." );



        char l_buf[ 128 ];
        
        l_len = read( l_sock, l_buf, sizeof( l_buf ) - 1 );
        if ( l_len == 0 )
        {
            log_msg( LOG_DEBUG, "Server closed socket." );
            break;
        }
        else if ( l_len < 0 )
        {
            log_msg( LOG_ERROR, "Unable to read data from server." );
            break;
        }
        
        l_buf[ l_len ] = '\0';
        
        log_msg( LOG_DEBUG, "Received %d bytes from server.", l_len );
        
        write( STDOUT_FILENO, l_buf, l_len );
        
        if ( !strncasecmp( l_buf, STR_CLOSE, strlen( STR_CLOSE ) ) )
        {
            log_msg( LOG_INFO, "Connection will be closed..." );
            break;
        }
        
        const char* l_ok = "OK\n";
        l_len = write( l_sock, l_ok, strlen( l_ok ) );
        if ( l_len < 0 )
        {
            log_msg( LOG_ERROR, "Unable to send OK to server." );
            break;
        }
        
        log_msg( LOG_DEBUG, "Sent OK to server." );
    }
    
    log_msg( LOG_INFO, "Consumer thread exiting." );
    pthread_exit( NULL );
}

void* producer_thread( void* t_arg )
{
    ProducerData* l_data = (ProducerData*)t_arg;
    int l_sock = l_data->sock;
    std::vector<std::string> l_names = l_data->names;
    delete l_data;
    
    if ( l_names.empty() )
    {
        log_msg( LOG_ERROR, "No names loaded, producer thread exiting." );
        pthread_exit( NULL );
    }
    
    size_t l_name_index = 0;
    
    log_msg( LOG_INFO, "Producer thread started. Sending names..." );
    
    while ( 1 )
    {
        int l_rate = g_names_per_minute;
        
        int l_delay_us = ( 60 * 1000000 ) / l_rate;
        
        std::string l_name = l_names[ l_name_index ];
        l_name_index = ( l_name_index + 1 ) % l_names.size();
        
        std::string l_msg = l_name + "\n";
        int l_len = write( l_sock, l_msg.c_str(), l_msg.length() );
        if ( l_len < 0 )
        {
            log_msg( LOG_ERROR, "Unable to send name to server." );
            break;
        }
        
        log_msg( LOG_DEBUG, "Sent name: %s", l_name.c_str() );
        
        char l_buf[ 16 ];
        l_len = read( l_sock, l_buf, sizeof( l_buf ) - 1 );
        if ( l_len <= 0 )
        {
            log_msg( LOG_ERROR, "Failed to receive OK from server." );
            break;
        }
        l_buf[ l_len ] = '\0';
        
        if ( strncmp( l_buf, "OK", 2 ) != 0 )
        {
            log_msg( LOG_ERROR, "Unexpected response from server: %s", l_buf );
        }
        else
        {
            log_msg( LOG_DEBUG, "Received OK from server." );
        }
        
        usleep( l_delay_us );
    }
    
    log_msg( LOG_INFO, "Producer thread exiting." );
    pthread_exit( NULL );
}

std::string setup_client_role( int t_sock_server )
{
    char l_buf[ 128 ];
    
    int l_len = read( t_sock_server, l_buf, sizeof( l_buf ) - 1 );
    if ( l_len <= 0 )
    {
        log_msg( LOG_ERROR, "Unable to read task request from server." );
        close( t_sock_server );
        exit( 1 );
    }
    l_buf[ l_len ] = '\0';
    
    write( STDOUT_FILENO, l_buf, l_len );
    
    char l_role_buf[ 64 ];
    l_len = read( STDIN_FILENO, l_role_buf, sizeof( l_role_buf ) - 1 );
    if ( l_len <= 0 )
    {
        log_msg( LOG_ERROR, "Unable to read role from stdin." );
        close( t_sock_server );
        exit( 1 );
    }
    l_role_buf[ l_len ] = '\0';
    
    if ( l_len > 0 && l_role_buf[ l_len - 1 ] == '\n' )
    {
        l_role_buf[ l_len - 1 ] = '\0';
        l_len--;
    }
    
    std::string l_role = std::string( l_role_buf );
    
    if ( l_role != STR_PRODUCER && l_role != STR_CONSUMER )
    {
        log_msg( LOG_ERROR, "Invalid role! Must be 'producer' or 'consumer'." );
        close( t_sock_server );
        exit( 1 );
    }
    
    log_msg( LOG_INFO, "Client role set to: '%s'", l_role.c_str() );
    
    std::string l_role_msg = l_role + "\n";
    l_len = write( t_sock_server, l_role_msg.c_str(), l_role_msg.length() );
    if ( l_len < 0 )
    {
        log_msg( LOG_ERROR, "Unable to send role to server." );
        close( t_sock_server );
        exit( 1 );
    }
    
    log_msg( LOG_INFO, "Role sent to server." );
    
    return l_role;
}

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

    std::string l_client_role = setup_client_role( l_sock_server );

    if ( l_client_role == STR_PRODUCER )
    {        
        std::vector<std::string> l_names = load_names( "jmena.txt" );
        if ( l_names.empty() )
        {
            log_msg( LOG_ERROR, "No names loaded, exiting." );
            close( l_sock_server );
            exit( 1 );
        }
        
        ProducerData* l_data = new ProducerData();
        l_data->sock = l_sock_server;
        l_data->names = l_names;
        
        pthread_t l_producer_thread;
        if ( pthread_create( &l_producer_thread, NULL, producer_thread, (void*)l_data ) != 0 )
        {
            log_msg( LOG_ERROR, "Unable to create producer thread." );
            delete l_data;
            close( l_sock_server );
            exit( 1 );
        }
        
        pthread_detach( l_producer_thread );
        log_msg( LOG_INFO, "Producer thread started." );
        
        while ( 1 )
        {
            char l_buf[ 128 ];
            int l_len = read( STDIN_FILENO, l_buf, sizeof( l_buf ) - 1 );
            
            if ( l_len == 0 )
            {
                log_msg( LOG_DEBUG, "Stdin closed." );
                break;
            }
            if ( l_len < 0 )
            {
                log_msg( LOG_ERROR, "Unable to read from stdin." );
                break;
            }
            
            l_buf[ l_len ] = '\0';
            
            g_names_per_minute = atoi( l_buf );
            if ( !strncasecmp( l_buf, STR_CLOSE, strlen( STR_CLOSE ) ) )
            {
                log_msg( LOG_INFO, "Closing connection..." );
                break;
            }
        }
    }
    else if ( l_client_role == STR_CONSUMER )
    {
        log_msg( LOG_INFO, "Running in CONSUMER mode." );
        
        ConsumerData* l_data = new ConsumerData();
        l_data->sock = l_sock_server;
        
        pthread_t l_consumer_thread;
        if ( pthread_create( &l_consumer_thread, NULL, consumer_thread, (void*)l_data ) != 0 )
        {
            log_msg( LOG_ERROR, "Unable to create consumer thread." );
            delete l_data;
            close( l_sock_server );
            exit( 1 );
        }
        
        pthread_detach( l_consumer_thread );
        log_msg( LOG_INFO, "Consumer thread started." );
        log_msg( LOG_INFO, "Enter 'close' to close application." );
        
        while ( 1 )
        {
            char l_buf[ 128 ];
            int l_len = read( STDIN_FILENO, l_buf, sizeof( l_buf ) - 1 );
            
            if ( l_len == 0 )
            {
                log_msg( LOG_DEBUG, "Stdin closed." );
                break;
            }
            if ( l_len < 0 )
            {
                log_msg( LOG_ERROR, "Unable to read from stdin." );
                break;
            }
            
            l_buf[ l_len ] = '\0';
            
            if ( !strncasecmp( l_buf, STR_CLOSE, strlen( STR_CLOSE ) ) )
            {
                log_msg( LOG_INFO, "Closing connection..." );
                break;
            }
        }
    }

    close( l_sock_server );

    return 0;
}