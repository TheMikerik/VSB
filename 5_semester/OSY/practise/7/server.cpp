//***************************************************************************
//
// Program example for labs in subject Operating Systems
//
// Petr Olivka, Dept. of Computer Science, petr.olivka@vsb.cz, 2017
//
// Example of socket server.
//
// This program is example of socket server and it allows to connect and serve
// multiple clients.
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
#include <vector>
#include <string>
#include <algorithm>

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

//***************************************************************************
// Simple mathematical expression evaluator
// Note: For simplicity, this evaluator handles expressions like "a+b", "a-b", "a*b", "a/b"

double evaluate_expression(const std::string& expr, std::string& error) {
    double a, b, result;
    char op;
    if (sscanf(expr.c_str(), "%lf %c %lf", &a, &op, &b) != 3) {
        error = "Invalid expression format.";
        return 0.0;
    }

    switch(op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/':
            if(b == 0){
                error = "Division by zero.";
                return 0.0;
            }
            result = a / b; break;
        default:
            error = "Unsupported operator.";
            return 0.0;
    }
    return result;
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

    log_msg(LOG_INFO, "---------------------------------------");
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
    if (listen(l_sock_listen, 5) < 0)
    {
        log_msg(LOG_ERROR, "Unable to listen on given port!");
        close(l_sock_listen);
        exit(1);
    }

    log_msg(LOG_INFO, "Enter 'quit' to quit server.");
    log_msg(LOG_INFO, "---------------------------------------\n");

    std::vector<int> clients;

    // Go!
    while (1)
    {
        std::vector<pollfd> poll_fds;
        pollfd server_fd;
        server_fd.fd = l_sock_listen;
        server_fd.events = POLLIN;
        poll_fds.push_back(server_fd);

        pollfd stdin_fd;
        stdin_fd.fd = STDIN_FILENO;
        stdin_fd.events = POLLIN;
        poll_fds.push_back(stdin_fd);

        for(auto client : clients){
            pollfd pfd;
            pfd.fd = client;
            pfd.events = POLLIN;
            poll_fds.push_back(pfd);
        }

        int l_poll = poll(poll_fds.data(), poll_fds.size(), -1);

        if (l_poll < 0)
        {
            if (errno == EINTR) continue;
            log_msg(LOG_ERROR, "Function poll failed!");
            break;
        }

        if (poll_fds[1].revents & POLLIN)
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
                for(auto client : clients){
                    close(client);
                }
                close(l_sock_listen);
                exit(0);
            }
        }

        if (poll_fds[0].revents & POLLIN)
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

            clients.push_back(l_sock_client);
            log_msg(LOG_INFO, "New client connected: %s:%d",
                    inet_ntoa(l_rsa.sin_addr), ntohs(l_rsa.sin_port));
        }

        for(size_t i = 2; i < poll_fds.size(); ++i){
            if(poll_fds[i].revents & POLLIN){
                int client_fd = poll_fds[i].fd;
                char buffer[1024];
                ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer)-1);
                if(bytes_read <= 0){
                    if(bytes_read < 0){
                        log_msg(LOG_ERROR, "Error reading from client %d.", client_fd);
                    } else {
                        log_msg(LOG_INFO, "Client %d disconnected.", client_fd);
                    }
                    close(client_fd);
                    clients.erase(std::remove(clients.begin(), clients.end(), client_fd), clients.end());
                }
                else{
                    buffer[bytes_read] = '\0';
                    std::string expr(buffer);
                    // Odstranění případných znaků nového řádku
                    expr.erase(std::remove(expr.begin(), expr.end(), '\n'), expr.end());
                    log_msg(LOG_INFO, "Received expression from client %d: %s", client_fd, expr.c_str());

                    // Vyhodnocení výrazu
                    std::string error;
                    double result = evaluate_expression(expr, error);
                    std::string response;
                    if(error.empty()){
                        response = expr + " = " + std::to_string(result) + "\n";
                    } else{
                        response = expr + " = ERROR: " + error + "\n";
                    }

                    // Rozeslání odpovědi všem klientům
                    for(auto client : clients){
                        ssize_t bytes_sent = write(client, response.c_str(), response.size());
                        if(bytes_sent < 0){
                            log_msg(LOG_ERROR, "Error sending to client %d.", client);
                        }
                    }

                    log_msg(LOG_INFO, "Broadcasted: %s", response.c_str());
                }
            }
        }
    }

    close(l_sock_listen);
    return 0;
}