#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#define HTTP_PORT 80
#define HTTPS_PORT 443

void *handle_client(void *arg);

int main()
{
	int server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock == -1) {
		perror("socket");
		_exit(-1);
	}

	struct sockaddr_in server_addr = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(HTTP_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
		perror("bind");
		_exit(-1);
	}

	if (listen(server_sock, 5) == -1) {
		perror("listen");
		_exit(-1);
	}

	while (1) {
		int client_sock = accept(server_sock, NULL, NULL);
		if (client_sock == -1) {
			perror("accept");
			continue;
		}

		pthread_t thread_id;
		if (pthread_create(&thread_id, NULL, &handle_client, &client_sock) != 0) {
			perror("pthread_create");
			(void) close(client_sock);
		}
/*
		if (pthread_detach(thread_id) == -1) {
			perror("pthread_detach");
			(void) close(client_sock);
		}
*/
	}

	return 0;
}

void *handle_client(void *arg)
{
	int client_sock = * (int *) arg;
	char hello[] = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
	while (1) {
		int bytes_to_read;
		if (ioctl(client_sock, FIONREAD, &bytes_to_read) == -1) {
			perror("ioctl");
			break;
		}
		if (bytes_to_read == 0)
			break;
		(void) printf("bytes_to_read: %d\n", bytes_to_read);

		char *buffer = (char *) malloc(bytes_to_read + 1);
		if (buffer == NULL) {
			perror("malloc");
			break;
		}

		if (recv(client_sock, buffer, bytes_to_read, 0) != bytes_to_read) {
			perror("recv");
			free(buffer);
			break;
		}
		buffer[bytes_to_read + 1] = '\0';
		(void) printf("%s\n", buffer);
		free(buffer);

		if (send(client_sock, hello, sizeof(hello), 0) != sizeof(hello)) {
			perror("send");
			break;
		}

		int html_file = open("test.html", O_RDONLY);
		if (html_file == -1) {
			perror("open");
			break;
		}

		off_t len = 0;
		if (sendfile(html_file, client_sock, 0, &len, NULL, 0) == -1) {
			perror("sendfile");
			(void) close(html_file);
			break;
		}
	}

	(void) close(client_sock);
	return NULL;
}
