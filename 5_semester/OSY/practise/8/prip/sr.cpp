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
#include <sstream>
#include <semaphore.h>
#include <pthread.h>

#define STR_QUIT    "quit"
#define MAX_PLAYERS 5

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
    vsnprintf(l_buf, sizeof(l_buf), t_form, l_arg);
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

struct hraci_misto {
    int socket;
    sem_t semafor;
};

hraci_misto g_mista[MAX_PLAYERS];
char g_slovo[128] = "a";

void inicializuj_mista() {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        g_mista[i].socket = -1;
        sem_init(&g_mista[i].semafor, 0, i == 0 ? 1 : 0);
    }
}

int najdi_volne_misto() {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (g_mista[i].socket == -1) return i;
    }
    return -1;
}

int dalsi(int P) {
    for (int i = 1; i <= MAX_PLAYERS; i++) {
        int index = (P + i) % MAX_PLAYERS;
        if (g_mista[index].socket != -1) return index;
    }
    return P; // Pokud je hráč jediný, vrátí sám sebe
}

void *hrac(void *arg) {
    int P = *(int *)arg;
    char buf[128];

    while (1) {
        sem_wait(&g_mista[P].semafor);

        // Odeslat aktuální slovo klientovi
        write(g_mista[P].socket, g_slovo, strlen(g_slovo));

        // Čekání na slovo od klienta
        int len = read(g_mista[P].socket, buf, sizeof(buf));
        if (len <= 0) break; // Klient se odpojil

        buf[len] = '\0';
        if (buf[0] == '*') { // Odpojení klienta
            g_mista[P].socket = -1;
            int PD = dalsi(P);
            sem_post(&g_mista[PD].semafor);
            break;
        }

        // Aktualizace slova
        strncpy(g_slovo, buf, sizeof(g_slovo));

        // Probudit dalšího hráče
        int PD = dalsi(P);
        sem_post(&g_mista[PD].semafor);
    }

    pthread_exit(NULL);
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

    inicializuj_mista();

    while (1)
    {
        sockaddr_in l_rsa;
        socklen_t l_rsa_size = sizeof(l_rsa);
        int l_sock_client = accept(l_sock_listen, (sockaddr *)&l_rsa, &l_rsa_size);
        if (l_sock_client == -1)
        {
            log_msg(LOG_ERROR, "Unable to accept new client.");
            continue;
        }

        int P = najdi_volne_misto();
        if (P == -1) {
            log_msg(LOG_INFO, "No free slots available.");
            close(l_sock_client);
            continue;
        }

        g_mista[P].socket = l_sock_client;

        pthread_t thread;
        int *arg = (int *)malloc(sizeof(int));
        *arg = P;
        pthread_create(&thread, NULL, hrac, arg);
        pthread_detach(thread);
    }

    close(l_sock_listen);
    return 0;
}