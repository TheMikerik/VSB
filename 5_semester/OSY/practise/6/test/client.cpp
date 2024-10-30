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
    if ( t_narg <= 3 || !strcmp(t_args[1], "-h") )
    {
        printf(
            "\n"
            "  Socket client example.\n"
            "\n"
            "  Use: %s [-h -d] ip_or_name port_number season\n"
            "\n"
            "    -d       debug mode \n"
            "    -h       this help\n"
            "    season   jaro, leto, podzim, zima\n"
            "\n", t_args[0] );

        exit(0);
    }

    if (!strcmp(t_args[1], "-d"))
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

//***************************************************************************
// Function to generate a random mathematical expression with + and -
// (You can remove or keep this function if not needed)
//***************************************************************************

int main(int t_narg, char **t_args)
{
    if (t_narg < 4) help(t_narg, t_args); // Now requires at least 4 arguments

    int l_port = 0;
    char *l_host = nullptr;
    char *season = nullptr;

    // parsing arguments
    for (int i = 1; i < t_narg; i++)
    {
        if (!strcmp(t_args[i], "-d"))
            g_debug = LOG_DEBUG;

        if (!strcmp(t_args[i], "-h"))
            help(t_narg, t_args);

        if (*t_args[i] != '-')
        {
            if (!l_host)
                l_host = t_args[i];
            else if (!l_port)
                l_port = atoi(t_args[i]);
            else if (!season)
                season = t_args[i];
        }
    }

    if (!l_host || !l_port || !season)
    {
        log_msg(LOG_INFO, "Host, port, or season is missing!");
        help(t_narg, t_args);
        exit(1);
    }

    // Validate season
    if (strcasecmp(season, "jaro") != 0 &&
        strcasecmp(season, "leto") != 0 &&
        strcasecmp(season, "podzim") != 0 &&
        strcasecmp(season, "zima") != 0 &&
        strcasecmp(season, "ukonceny") != 0)
    {
        log_msg(LOG_INFO, "Invalid season name: %s", season);
        help(t_narg, t_args);
        exit(1);
    }

    log_msg(LOG_INFO, "Connection to '%s':%d.", l_host, l_port);

    addrinfo l_ai_req, *l_ai_ans;
    bzero(&l_ai_req, sizeof(l_ai_req));
    l_ai_req.ai_family = AF_INET;
    l_ai_req.ai_socktype = SOCK_STREAM;

    int l_get_ai = getaddrinfo(l_host, NULL, &l_ai_req, &l_ai_ans);
    if (l_get_ai)
    {
        log_msg(LOG_ERROR, "Unknown host name!");
        exit(1);
    }

    sockaddr_in l_cl_addr = *(sockaddr_in*)l_ai_ans->ai_addr;
    l_cl_addr.sin_port = htons(l_port);
    freeaddrinfo(l_ai_ans);

    // socket creation
    int l_sock_server = socket(AF_INET, SOCK_STREAM, 0);
    if (l_sock_server == -1)
    {
        log_msg(LOG_ERROR, "Unable to create socket.");
        exit(1);
    }

    // connect to server
    if (connect(l_sock_server, (sockaddr*)&l_cl_addr, sizeof(l_cl_addr)) < 0)
    {
        log_msg(LOG_ERROR, "Unable to connect to server.");
        exit(1);
    }

    socklen_t l_lsa = sizeof(l_cl_addr);
    // my IP
    getsockname(l_sock_server, (sockaddr*)&l_cl_addr, &l_lsa);
    log_msg(LOG_INFO, "My IP: '%s'  port: %d",
            inet_ntoa(l_cl_addr.sin_addr), ntohs(l_cl_addr.sin_port));
    // server IP
    getpeername(l_sock_server, (sockaddr*)&l_cl_addr, &l_lsa);
    log_msg(LOG_INFO, "Server IP: '%s'  port: %d",
            inet_ntoa(l_cl_addr.sin_addr), ntohs(l_cl_addr.sin_port));

    // Send the season request to the server
    size_t season_len = strlen(season);
    char season_request[256];
    snprintf(season_request, sizeof(season_request), "%s\n", season);

    ssize_t bytes_sent = write(l_sock_server, season_request, strlen(season_request));
    if (bytes_sent < 0)
    {
        log_msg(LOG_ERROR, "Unable to send season request to server.");
        close(l_sock_server);
        exit(1);
    }
    else
    {
        log_msg(LOG_DEBUG, "Sent %ld bytes to server: %s", bytes_sent, season_request);
    }

    // Prepare to receive image data
    pid_t pid = getpid();
    char img_filename[256];
    snprintf(img_filename, sizeof(img_filename), "%d.img", pid);

    FILE* img_fp = fopen(img_filename, "wb");
    if (!img_fp)
    {
        log_msg(LOG_ERROR, "Unable to create image file '%s'.", img_filename);
        close(l_sock_server);
        exit(1);
    }

    log_msg(LOG_INFO, "Receiving image data and saving to '%s'.", img_filename);

    // Receive image data in chunks and write to file
    char recv_buffer[1024];
    ssize_t bytes_received;
    while ((bytes_received = read(l_sock_server, recv_buffer, sizeof(recv_buffer))) > 0)
    {
        size_t bytes_written = fwrite(recv_buffer, 1, bytes_received, img_fp);
        if (bytes_written < (size_t)bytes_received)
        {
            log_msg(LOG_ERROR, "Failed to write to image file.");
            break;
        }
    }

    if (bytes_received < 0)
    {
        log_msg(LOG_ERROR, "Error reading image data from server.");
    }
    else
    {
        log_msg(LOG_INFO, "Image data received successfully.");
    }

    fclose(img_fp);
    close(l_sock_server);

    // Fork a child process to display the image
    pid_t child_pid = fork();
    if (child_pid < 0)
    {
        log_msg(LOG_ERROR, "Failed to fork child process.");
        exit(1);
    }

    if (child_pid == 0)
    {
        // Child process: execute the display command
        execlp("magick", "magick", "display", img_filename, (char*)NULL);

        // If execlp returns, an error occurred
        log_msg(LOG_ERROR, "Failed to execute magick command.");
        exit(1);
    }
    else
    {
        // Parent process: wait for the child to finish
        int status;
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status))
        {
            log_msg(LOG_INFO, "Image display completed with exit code %d.", WEXITSTATUS(status));
        }
        else
        {
            log_msg(LOG_ERROR, "Image display terminated abnormally.");
        }
    }

    return 0;
}