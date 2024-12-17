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
#include <pthread.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>  

#define STR_CLOSE "close"

//***************************************************************************
// log messages

#define LOG_ERROR 0 // errors
#define LOG_INFO 1	// information and notifications
#define LOG_DEBUG 2 // debug messages

// debug flag
int g_debug = LOG_INFO;

void log_msg(int t_log_level, const char *t_form, ...)
{
	const char *out_fmt[] = {
		"ERR: (%d-%s) %s\n",
		"INF: %s\n",
		"DEB: %s\n"};

	if (t_log_level && t_log_level > g_debug)
		return;

	char l_buf[1024];
	va_list l_arg;
	va_start(l_arg, t_form);
	vsprintf(l_buf, t_form, l_arg);
	va_end(l_arg);

	switch (t_log_level)
	{
	case LOG_INFO:
	case LOG_DEBUG:
		fprintf(stdout, out_fmt[t_log_level], l_buf);
		break;

	case LOG_ERROR:
		fprintf(stderr, out_fmt[t_log_level], errno, strerror(errno), l_buf);
		break;
	}
}

//***************************************************************************
// help

void help(int t_narg, char **t_args)
{
	if (t_narg <= 1 || !strcmp(t_args[1], "-h"))
	{
		printf(
			"\n"
			"  Socket client example.\n"
			"\n"
			"  Use: %s [-h -d] ip_or_name port_number\n"
			"\n"
			"    -d  debug mode \n"
			"    -h  this help\n"
			"\n",
			t_args[0]);

		exit(0);
	}

	if (!strcmp(t_args[1], "-d"))
		g_debug = LOG_DEBUG;
}

//***************************************************************************
char g_hex_char[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
char g_hex_res[16] = "LED #00\n";
void int_to_hex(int n)
{
	int a = n & 0x000F;
	int b = n >> 4 & 0x00FF;
	g_hex_res[6] = g_hex_char[a];
	g_hex_res[5] = g_hex_char[b];
}

void* handle_led(void* arg)
{
	int server = *((int*) arg);
	printf("starting led task\n");
	for (int i = 0; i < 8; i++)
	{
		int_to_hex(1 << i);
		write(server, g_hex_res, strlen(g_hex_res));
		usleep(1000*100);
	}
	write(server, "LED #00\n", strlen("LED #00\n"));
	return nullptr;
}

void* handle_led_reverse(void* arg)
{
	int server = *((int*) arg);
	printf("starting led task\n");
	for (int i = 7; i >= 0; i--)
	{
		int_to_hex(1 << i);
		write(server, g_hex_res, strlen(g_hex_res));
		usleep(1000*100);
	}
	write(server, "LED #00\n", strlen("LED #00\n"));
	return nullptr;
}

char g_hex_res_rgb[16] = "RGB #000000\n";
void int_to_hex_rgb(int* n)
{
	for (int i = 0; i < 3; i++)
	{
		int a = n[i] & 0x000F;
		int b = n[i] >> 4 & 0x000F;
		g_hex_res_rgb[5+i*2+1] = g_hex_char[a];
		g_hex_res_rgb[5+(i*2)+0] = g_hex_char[b];
	}
	printf("SEND: %s\n", g_hex_res_rgb);
}

int do_rgb = 0;
void* handle_rgb(void* arg)
{
	int server = *((int*) arg);
	char buf[16] = {};
	int c = 0;
	int rgb[3] = {0,0,0};
	int dir = 1;
	do_rgb = 1;
	while (do_rgb)
	{
		for (int i = 0; i < 64; i++)
		{
			if (do_rgb == 0) break;
			rgb[c] += 4 * dir;
			if (rgb[c] > 255) rgb[c] = 255;
			if (rgb[c] < 0) rgb[c] = 0;

			int_to_hex_rgb(rgb);
			write(server, g_hex_res_rgb, strlen(g_hex_res_rgb));

			usleep(1000* 20);
		}
		dir *= -1;
		if (rgb[c] == 0) c++;
		if (c > 2) c = 0;
	}
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	int_to_hex_rgb(rgb);
	write(server, g_hex_res_rgb, strlen(g_hex_res_rgb));
	return nullptr;
}
pthread_t t_rgb;


int main(int t_narg, char **t_args)
{

	if (t_narg <= 3)
		help(t_narg, t_args);

	int l_port = 0;
	char *l_host = nullptr;
	char *nick = nullptr;

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
			else if (!nick)
				nick = t_args[i];
		}
	}

	if (!l_host || !l_port)
	{
		log_msg(LOG_INFO, "Host or port is missing!");
		help(t_narg, t_args);
		exit(1);
	}

	log_msg(LOG_INFO, "Connection to '%s':%d.", l_host, l_port);

	addrinfo l_ai_req, *l_ai_ans;
	bzero(&l_ai_req, sizeof(l_ai_req));
	l_ai_req.ai_family = AF_INET;
	l_ai_req.ai_socktype = SOCK_STREAM;

	int l_get_ai = getaddrinfo(l_host, nullptr, &l_ai_req, &l_ai_ans);
	if (l_get_ai)
	{
		log_msg(LOG_ERROR, "Unknown host name!");
		exit(1);
	}

	sockaddr_in l_cl_addr = *(sockaddr_in *)l_ai_ans->ai_addr;
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
	if (connect(l_sock_server, (sockaddr *)&l_cl_addr, sizeof(l_cl_addr)) < 0)
	{
		log_msg(LOG_ERROR, "Unable to connect server.");
		exit(1);
	}

	// list of fd sources
	pollfd l_read_poll[2];

	l_read_poll[0].fd = STDIN_FILENO;
	l_read_poll[0].events = POLLIN;
	l_read_poll[1].fd = l_sock_server;
	l_read_poll[1].events = POLLIN;

	// go!
	while (1)
	{
		char l_buf[128] = {};

		// select from fds
		int pol = poll(l_read_poll, 2, 3000);

		if (pol < 0)
			break;

		// data on stdin?
		if (l_read_poll[0].revents & POLLIN)
		{
			//  read from stdin
			int l_len = read(STDIN_FILENO, l_buf, sizeof(l_buf));
			if (l_len < 0)
				log_msg(LOG_ERROR, "Unable to read from stdin.");
			else
				log_msg(LOG_DEBUG, "Read %d bytes from stdin.", l_len);

			// send data to server
			l_len = write(l_sock_server, l_buf, l_len);
			if (l_len < 0)
				log_msg(LOG_ERROR, "Unable to send data to server.");
			else
				log_msg(LOG_DEBUG, "Sent %d bytes to server.", l_len);

			// request to close?
			if (!strncasecmp(l_buf, STR_CLOSE, strlen(STR_CLOSE)))
			{
				log_msg(LOG_INFO, "\nConnection will be closed...");
				break;
			}
		}

		// data from server?
		if (l_read_poll[1].revents & POLLIN)
		{
			// read data from server
			int l_len = read(l_sock_server, l_buf, sizeof(l_buf));
			if (!l_len)
			{
				log_msg(LOG_DEBUG, "Server closed socket.");
				break;
			}
			else if (l_len < 0)
			{
				log_msg(LOG_ERROR, "Unable to read data from server.");
				break;
			}
			else
				log_msg(LOG_DEBUG, "Read %d bytes from server.", l_len);

			// display on stdout
			l_len = write(STDOUT_FILENO, l_buf, l_len);
			if (l_len < 0)
				log_msg(LOG_ERROR, "Unable to write to stdout.");

			if (strncmp(l_buf, "BTN ", 4) == 0)
			{
				pthread_t t;
				int c = l_sock_server;
				if (l_buf[4] == '1') pthread_create(&t, nullptr, handle_led, &c);
				else if (l_buf[5] == '1') pthread_create(&t, nullptr, handle_led_reverse, &c);
				else if (l_buf[6] == '1' && do_rgb == 0) pthread_create(&t_rgb, nullptr, handle_rgb, &c);
				else if (l_buf[7] == '1') 
				{
					do_rgb = 0;
					//pthread_cancel(t_rgb);
				}
			}

			// request to close?
			if (!strncasecmp(l_buf, STR_CLOSE, strlen(STR_CLOSE)))
			{
				log_msg(LOG_INFO, "\nConnection will be closed...");
				break;
			}
		}
	}

	// close socket
	close(l_sock_server);

	return 0;
}