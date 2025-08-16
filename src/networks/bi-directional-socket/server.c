#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <errno.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 512
#define SOCKET_FILE "socket.sock"

#define print_debug(...) do { \
    if (dbgfp) { \
        fprintf(dbgfp, "SERVER  %17s:%-4d  %17s() :: ", __FILE__, __LINE__, __FUNCTION__); \
        fprintf(dbgfp, __VA_ARGS__); \
        fprintf(dbgfp, "\n"); \
    } \
} while(0);

FILE *dbgfp;

enum e_sockt_data {
	REQ,
	REPLY,
	EVENT,
};

typedef struct sockt_data_st {
	int type;
	char stype[16];
	char data[BUFFER_SIZE];
} sockt_data_t;

/* Client event handler */
void *notify_events(void *arg)
{
	int i = 0;
	int n = -1;
	int freq = 10;
	int sockfd = *((int *)arg);
	sockt_data_t sockt_data = { 0 };
	char *buffer = "#### SAMPLE EVENT MESSAGE ####";

	print_debug("called: socket: %d", sockfd);

	while(1) {
		sleep(freq);
		memset(&sockt_data, 0x00, sizeof(sockt_data));
		sockt_data.type = EVENT;
		strcpy(sockt_data.stype, "EVENT");
		sprintf(sockt_data.data, "[%d] [%s]", i++, buffer);

		print_debug("send event (%d sec) '%s' ...", freq, sockt_data.data);
		n = send(sockfd, &sockt_data, sizeof(sockt_data), 0);
		if (n < 0) {
			print_debug("send failed: %s", strerror(errno));
		}

		print_debug("send event completed: written %d bytes", n);
	}

	pthread_exit(NULL);
}

/* Client request handler */
void *handle_request(void *arg)
{
	int n = -1;
	int sockfd = *((int *)arg);
	ssize_t bytes_received = 0;
	//char buffer[BUFFER_SIZE] = { 0 };
	sockt_data_t sockt_data = { 0 };

	print_debug("called: socket: %d", sockfd);

	while(1) {
		// Receive data from Client
		memset(&sockt_data, 0x00, sizeof(sockt_data));
		print_debug("waiting to receive client request ...");
		bytes_received = recv(sockfd, &sockt_data, sizeof(sockt_data), 0);
		print_debug("received client request");
		if (bytes_received < 0) {
			print_debug("error in recv: %s", strerror(errno));
		} else if (bytes_received == 0) {
			print_debug("no data received: client might disconnected.");
			print_debug("exiting thread.");
			break;
		} else {
			// Echo back to client
			sockt_data.type = REPLY;
			strcpy(sockt_data.stype, "REPLY");
			print_debug("send reply '%s'", sockt_data.data);
			n = send(sockfd, &sockt_data, sizeof(sockt_data), 0);
			if (n < 0) {
				print_debug("send failed: %s", strerror(errno));
			}

			print_debug("send reply completed: written %d bytes", n);
		}
	}

	pthread_exit(NULL);
}

int main()
{
	int server_socket, client_socket;
	pthread_t evt_thread, req_thread;
	struct sockaddr_un server_addr, client_addr;
	socklen_t addr_len = sizeof(client_addr);

	dbgfp = stderr;

	print_debug("socket '%s'", SOCKET_FILE);

	if ((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		print_debug("error creating socket: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}

	server_addr.sun_family = AF_UNIX;
	strncpy(server_addr.sun_path, SOCKET_FILE, sizeof(server_addr.sun_path) - 1);

	unlink(SOCKET_FILE);

	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		print_debug("error in bind: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (listen(server_socket, MAX_EVENTS) == -1) {
		print_debug("error in listen: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}

	print_debug("server listening on socket: %s", SOCKET_FILE);

	while (1) {
		if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len)) == -1) {
			print_debug("error in accept: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}

		print_debug("client connected");

		pthread_create(&evt_thread, NULL, notify_events,  &client_socket);
		pthread_create(&req_thread, NULL, handle_request, &client_socket);

		pthread_join(evt_thread, NULL);
		pthread_join(req_thread, NULL);

		close(client_socket);
		print_debug("client socket closed.");
	}

	close(server_socket);
	unlink(SOCKET_FILE);
	print_debug("process end!");

	return 0;
}

/* EOF */
