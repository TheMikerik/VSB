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
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <pthread.h>

#define STR_CLOSE               "close"

//***************************************************************************
// log messages

#define LOG_ERROR               0       // errors
#define LOG_INFO                1       // information and notifications
#define LOG_DEBUG               2       // debug messages

// debug flag
int g_debug = LOG_INFO;
int g_sock_server = -1;
int g_running = 1;  // Flag pro ukončení vláken

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
// Thread funkce pro čtení z klávesnice a odesílání na server

void* thread_read_stdin( void* t_arg )
{
    int l_sock = *(int*)t_arg;
    char l_buf[ 128 ];
    
    while ( g_running )
    {
        // Čtení z stdin
        int l_len = read( STDIN_FILENO, l_buf, sizeof( l_buf ) );
        
        if ( l_len == 0 )
        {
            log_msg( LOG_DEBUG, "Stdin closed." );
            g_running = 0;
            break;
        }
        
        if ( l_len < 0 )
        {
            log_msg( LOG_ERROR, "Unable to read from stdin." );
            g_running = 0;
            break;
        }
        
        log_msg( LOG_DEBUG, "Read %d bytes from stdin.", l_len );
        
        // Odeslání na server
        int l_sent = write( l_sock, l_buf, l_len );
        if ( l_sent < 0 )
        {
            log_msg( LOG_ERROR, "Unable to send data to server." );
            g_running = 0;
            break;
        }
        
        log_msg( LOG_DEBUG, "Sent %d bytes to server.", l_sent );
        
        // Kontrola "close" příkazu
        if ( !strncasecmp( l_buf, STR_CLOSE, strlen( STR_CLOSE ) ) )
        {
            log_msg( LOG_INFO, "Closing connection..." );
            g_running = 0;
            break;
        }
    }
    
    pthread_exit( NULL );
}

//***************************************************************************
// Thread funkce pro čtení ze socketu a výpis na stdout

void* thread_read_socket( void* t_arg )
{
    int l_sock = *(int*)t_arg;
    char l_buf[ 128 ];
    
    while ( g_running )
    {
        // Čtení ze socketu
        int l_len = read( l_sock, l_buf, sizeof( l_buf ) );
        
        if ( l_len == 0 )
        {
            log_msg( LOG_DEBUG, "Server closed socket." );
            g_running = 0;
            break;
        }
        
        if ( l_len < 0 )
        {
            if ( g_running )  // Ignorovat chybu pokud už ukončujeme
            {
                log_msg( LOG_ERROR, "Unable to read data from server." );
            }
            g_running = 0;
            break;
        }
        
        log_msg( LOG_DEBUG, "Read %d bytes from server.", l_len );
        
        // Výpis na stdout
        int l_written = write( STDOUT_FILENO, l_buf, l_len );
        if ( l_written < 0 )
        {
            log_msg( LOG_ERROR, "Unable to write to stdout." );
            break;
        }
        
        // Kontrola "close" zprávy od serveru
        if ( !strncasecmp( l_buf, STR_CLOSE, strlen( STR_CLOSE ) ) )
        {
            log_msg( LOG_INFO, "Server requested connection close..." );
            g_running = 0;
            break;
        }
    }
    
    pthread_exit( NULL );
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

    g_sock_server = l_sock_server;  // Uložit globálně pro vlákna

    uint l_lsa = sizeof( l_cl_addr );
    // my IP
    getsockname( l_sock_server, ( sockaddr * ) &l_cl_addr, &l_lsa );
    log_msg( LOG_INFO, "My IP: '%s'  port: %d",
             inet_ntoa( l_cl_addr.sin_addr ), ntohs( l_cl_addr.sin_port ) );
    // server IP
    getpeername( l_sock_server, ( sockaddr * ) &l_cl_addr, &l_lsa );
    log_msg( LOG_INFO, "Server IP: '%s'  port: %d",
             inet_ntoa( l_cl_addr.sin_addr ), ntohs( l_cl_addr.sin_port ) );

    log_msg( LOG_INFO, "Enter 'close' to close application." );

    // Vytvořit vlákno pro čtení z klávesnice
    pthread_t l_thread_stdin;
    int l_result = pthread_create( &l_thread_stdin, NULL, thread_read_stdin, &l_sock_server );
    if ( l_result != 0 )
    {
        log_msg( LOG_ERROR, "Unable to create stdin thread!" );
        close( l_sock_server );
        exit( 1 );
    }

    // Vytvořit vlákno pro čtení ze socketu
    pthread_t l_thread_socket;
    l_result = pthread_create( &l_thread_socket, NULL, thread_read_socket, &l_sock_server );
    if ( l_result != 0 )
    {
        log_msg( LOG_ERROR, "Unable to create socket thread!" );
        g_running = 0;
        pthread_cancel( l_thread_stdin );
        close( l_sock_server );
        exit( 1 );
    }

    // Čekat na ukončení jednoho z vláken
    pthread_join( l_thread_stdin, NULL );
    pthread_join( l_thread_socket, NULL );

    // close socket
    close( l_sock_server );

    return 0;
}