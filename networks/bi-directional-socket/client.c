#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <errno.h>

#define BUFFER_SIZE 512
#define SOCKET_FILE "socket.sock"

#define print_debug(...) do { \
    if (dbgfp) { \
        fprintf(dbgfp, "CLIENT  %17s:%-4d  %17s() :: ", __FILE__, __LINE__, __FUNCTION__); \
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

/* Handle client request */
void *send_request(void *arg)
{
	int i = 0;
	int n = -1;
	int freq = 20;
	int sockfd = *((int *)arg);
	sockt_data_t sockt_data = { 0 };
	char *buffer = "==== SAMPLE REQUEST ====";

	print_debug("called: socket: %d", sockfd);

	while(1) {
		sleep(freq);
		memset(&sockt_data, 0x00, sizeof(sockt_data));

		sockt_data.type = REQ;
		strcpy(sockt_data.stype, "REQ");
		sprintf(sockt_data.data, "[%d] [%s]", i++, buffer);

		print_debug("send request (%d sec) '%s' ...", freq, sockt_data.data);
		n = send(sockfd, &sockt_data, sizeof(sockt_data), 0);
		if (n < 0) {
			print_debug("send failed: %s", strerror(errno));
		}

		print_debug("send request completed: written %d bytes", n);
	}

	pthread_exit(NULL);
}

/* Handle events received from server */
int event_handler(sockt_data_t *p_sockt_data)
{
	if (p_sockt_data == NULL) {
		print_debug("ERROR: sockt_data is NULL");
		return -1;
	}

	print_debug("======================================================");
	print_debug("[%d: %s] %s", p_sockt_data->type, p_sockt_data->stype, p_sockt_data->data);
	print_debug("======================================================");

	return 0;
}

/* Handle client request reply received from server which sent in send_request call */
int request_handler(sockt_data_t *p_sockt_data)
{
	if (p_sockt_data == NULL) {
		print_debug("ERROR: sockt_data is NULL");
		return -1;
	}

	print_debug("======================================================");
	print_debug("[%d: %s] %s", p_sockt_data->type, p_sockt_data->stype, p_sockt_data->data);
	print_debug("======================================================");

	return 0;
}

/* Client socket multiplexer */
void *multiplexer(void *arg)
{
	int ret = -1;
	fd_set read_fds;
	ssize_t bytes_received;
	sockt_data_t sockt_data;
	int sockfd = *((int *)arg);

	print_debug("called: socket: %d", sockfd);

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);

		print_debug("waiting to receive updates ...");
		ret = select(sockfd + 1, &read_fds, NULL, NULL, NULL);
        if (ret == -1) {
            if (errno != EINTR) {
				print_debug("select error: %s", strerror(errno));
				print_debug("exiting thread.");
				break;
            }
        } else if (ret > 0) {
            if (FD_ISSET(sockfd, &read_fds)) {
				memset(&sockt_data, 0, sizeof(sockt_data));
				bytes_received = recv(sockfd, &sockt_data, sizeof(sockt_data), 0);
                if (bytes_received < 0) {
					print_debug("recv error: %s", strerror(errno));
					print_debug("exiting thread.");
					break;
                } else if (bytes_received == 0) {
                    print_debug("server disconnected");
                    break;
                } else {
					/* Handle socket change */
					print_debug("received %u bytes from server", bytes_received);
#if 0
					print_debug("=======================================");
					print_debug("[ %d: %s ] %s", sockt_data.type, sockt_data.stype, sockt_data.data);
					print_debug("=======================================");
#endif
					switch(sockt_data.type) {
						case REPLY:
							request_handler(&sockt_data);
							break;

						case EVENT:
							event_handler(&sockt_data);
							break;

						default:
							print_debug("ERROR: invalid socket data type");
							break;
					};
				}
            }
        } else {
            print_debug("select: timed out. no data received");
        }
    }

	pthread_exit(NULL);
}

int main()
{
	int sockfd;
	struct sockaddr_un server_addr;
	pthread_t evt_thread, req_thread;

	dbgfp = stderr;

	if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		print_debug("Error creating socket: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}

	server_addr.sun_family = AF_UNIX;
	strncpy(server_addr.sun_path, SOCKET_FILE, sizeof(server_addr.sun_path) - 1);

	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		print_debug("error in connect: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}

	print_debug("connected to server");

	pthread_create(&evt_thread, NULL, multiplexer,  &sockfd);
	pthread_create(&req_thread, NULL, send_request, &sockfd);

	pthread_join(evt_thread, NULL);
	pthread_join(req_thread, NULL);

	close(sockfd);
	print_debug("process end!");

	return 0;
}

/* EOF */
