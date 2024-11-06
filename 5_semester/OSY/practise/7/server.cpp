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
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/stat.h>

#define STR_CLOSE   "close"
#define STR_QUIT    "quit"

//***************************************************************************
// log messages

#define LOG_ERROR               0       // errors
#define LOG_INFO                1       // information and notifications
#define LOG_DEBUG               2       // debug messages

// debug flag
int g_debug = LOG_INFO;

void log_msg(int t_log_level, const char *t_form, ...)
{
    const char *out_fmt[] = {
        "ERR: (%d-%s) %s\n",
        "INF: %s\n",
        "DEB: %s\n"
    };

    if (t_log_level && t_log_level > g_debug) return;

    char l_buf[2048];
    va_list l_arg;
    va_start(l_arg, t_form);
    vsprintf(l_buf, t_form, l_arg);
    va_end(l_arg);

    switch (t_log_level)
    {
    case LOG_INFO:
    case LOG_DEBUG:
        fprintf(stdout, out_fmt[t_log_level], l_buf);
        fflush(stdout);
        break;

    case LOG_ERROR:
        fprintf(stderr, out_fmt[t_log_level], errno, strerror(errno), l_buf);
        fflush(stderr);
        break;
    }
}

//***************************************************************************
// Function to display help

void help(int t_narg, char **t_args)
{
    if (t_narg <= 1 || !strcmp(t_args[1], "-h"))
    {
        printf(
            "\n"
            "  Socket server example.\n"
            "\n"
            "  Use: %s [-h -d] port_number\n"
            "\n"
            "    -d  debug mode \n"
            "    -h  this help\n"
            "\n", t_args[0]);

        exit(0);
    }

    if (!strcmp(t_args[1], "-d"))
        g_debug = LOG_DEBUG;
}

void send_image(int client_sock, const char* season)
{
    char image_file[256];
    if( strcmp( season, "jaro") == 0 || strcmp( season, "podzim") == 0){
        snprintf(image_file, sizeof(image_file), "%s.jpg", season);
    } else if( strcmp( season, "leto") == 0 || strcmp( season, "zima") == 0){
        snprintf(image_file, sizeof(image_file), "%s.png", season);
    }

    int fd = open(image_file, O_RDONLY);
    if (fd < 0)
    {
        log_msg(LOG_ERROR, "Unable to open image file: %s", image_file);
        close(client_sock);
        exit(1);
    }

    struct stat st;
    if (fstat(fd, &st) < 0)
    {
        log_msg(LOG_ERROR, "Unable to get file size: %s", image_file);
        close(fd);
        close(client_sock);
        exit(1);
    }
    off_t filesize = st.st_size;


    size_t block = 1024;

    int blocks = filesize / block;
    if (filesize % block != 0) blocks += 1;
    double block_delay = 15.0 / blocks;

    char buffer[block];
    ssize_t bytes_read, bytes_sent;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        ssize_t total_sent = 0;
        while (total_sent < bytes_read)
        {
            bytes_sent = write(client_sock, buffer + total_sent, bytes_read - total_sent);
            if (bytes_sent < 0)
            {
                log_msg(LOG_ERROR, "Unable to send data to client.");
                close(fd);
                close(client_sock);
                exit(1);
            }
            total_sent += bytes_sent;
        }

        usleep(block_delay * 1000000);
    }

    if (bytes_read < 0)
    {
        log_msg(LOG_ERROR, "Error reading image file: %s", image_file);
    }

    log_msg(LOG_INFO, "Finished sending image: %s", image_file);
    close(fd);
    close(client_sock);
    exit(0);
}

//***************************************************************************

int main(int t_narg, char **t_args)
{
    if (t_narg <= 1) help(t_narg, t_args);

    int l_port = 0;

    for (int i = 1; i < t_narg; i++)
    {
        if (!strcmp(t_args[i], "-d"))
            g_debug = LOG_DEBUG;

        if (!strcmp(t_args[i], "-h"))
            help(t_narg, t_args);

        if (*t_args[i] != '-' && !l_port)
        {
            l_port = atoi(t_args[i]);
            break;
        }
    }

    if (l_port <= 0)
    {
        log_msg(LOG_INFO, "Bad or missing port number %d!", l_port);
        help(t_narg, t_args);
    }

    log_msg(LOG_INFO, "Server will listen on port: %d.", l_port);

    // Socket creation
    int l_sock_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (l_sock_listen == -1)
    {
        log_msg(LOG_ERROR, "Unable to create socket.");
        exit(1);
    }

    in_addr l_addr_any = {INADDR_ANY};
    sockaddr_in l_srv_addr;
    l_srv_addr.sin_family = AF_INET;
    l_srv_addr.sin_port = htons(l_port);
    l_srv_addr.sin_addr = l_addr_any;

    // Enable the port number reusing
    int l_opt = 1;
    if (setsockopt(l_sock_listen, SOL_SOCKET, SO_REUSEADDR, &l_opt, sizeof(l_opt)) < 0)
        log_msg(LOG_ERROR, "Unable to set socket option!");

    // Assign port number to socket
    if (bind(l_sock_listen, (const sockaddr *)&l_srv_addr, sizeof(l_srv_addr)) < 0)
    {
        log_msg(LOG_ERROR, "Bind failed!");
        close(l_sock_listen);
        exit(1);
    }

    // Listening on set port
    if (listen(l_sock_listen, 5) < 0) // Increased backlog to handle multiple clients
    {
        log_msg(LOG_ERROR, "Unable to listen on given port!");
        close(l_sock_listen);
        exit(1);
    }

    log_msg(LOG_INFO, "Enter 'quit' to quit server.");

    // Go!
    while (1)
    {
        int l_sock_client = -1;

        // list of fd sources
        pollfd l_read_poll[ 2 ];

        l_read_poll[ 0 ].fd = STDIN_FILENO;
        l_read_poll[ 0 ].events = POLLIN;
        l_read_poll[ 1 ].fd = l_sock_listen;
        l_read_poll[ 1 ].events = POLLIN;

        int l_poll = poll(l_read_poll, 2, -1);

        if (l_poll < 0)
        {
            if (errno == EINTR) continue;
            log_msg(LOG_ERROR, "Function poll failed!");
            break;
        }

        if (l_read_poll[0].revents & POLLIN)
        { 
            
            char buf[128];
            int len = read(STDIN_FILENO, buf, sizeof(buf) - 1);
            if (len < 0)
            {
                log_msg(LOG_DEBUG, "Unable to read from stdin!");
                continue;
            }

            buf[len] = '\0';
            log_msg(LOG_DEBUG, "Read %d bytes from stdin: %s", len, buf);

            // Check if the input is the "quit" command
            if (!strncmp(buf, STR_QUIT, strlen(STR_QUIT)))
            {
                log_msg(LOG_INFO, "Request to 'quit' entered.");
                close(l_sock_listen);
                exit(0);
            }
        }

        if (l_read_poll[1].revents & POLLIN)
        { 
            sockaddr_in l_rsa;
            socklen_t l_rsa_size = sizeof(l_rsa);
            int l_sock_client = accept(l_sock_listen, (sockaddr *)&l_rsa, &l_rsa_size);
            if (l_sock_client < 0)
            {
                if (errno == EINTR) continue; // Interrupted by signal
                log_msg(LOG_ERROR, "Unable to accept new client.");
                continue;
            }

            pid_t pid = fork();
            if (pid == 0)
            {
                log_msg(LOG_DEBUG, "Forked child process with PID %d to handle client.", getpid());
                close(l_sock_listen);

                char client_ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(l_rsa.sin_addr), client_ip, INET_ADDRSTRLEN);
                log_msg(LOG_INFO, "Client connected from %s:%d", client_ip, ntohs(l_rsa.sin_port));

                char season_buf[128];
                ssize_t bytes_read = 0;
                size_t total_read = 0;
                log_msg(LOG_DEBUG, "Child process %d: Starting to read season request.", getpid());
                while ((bytes_read = read(l_sock_client, season_buf + total_read, 1)) > 0)
                {
                    if (season_buf[total_read] == '\n') break;
                    total_read += bytes_read;
                    if (total_read >= sizeof(season_buf) - 1) break;
                }
                season_buf[total_read] = '\0';
                log_msg(LOG_INFO, "Received season request: %s", season_buf);

                send_image(l_sock_client, season_buf);
                exit(0);
            }
            else
            {
                log_msg(LOG_DEBUG, "Forked child process with PID %d to handle client.", pid);
                close(l_sock_client);
            }
        }
    }

    close(l_sock_listen);
    return 0;
}