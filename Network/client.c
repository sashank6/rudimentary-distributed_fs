#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<errno.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 34343

void handle_error(char *s) {
	printf("Error: %s Reason: %s\n", s, strerror(errno));
	exit(EXIT_FAILURE);
}

int main() {

	int socket_fd;
	struct sockaddr_in serv_addr;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		handle_error("Socket Opening Error");

	struct hostent *server;
	server = gethostbyname("192.168.1.115");
	if (server == NULL)
		handle_error("No valid host");

	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(PORT);

	if (connect(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))
			== -1)
		handle_error("Connection Error");
	close(socket_fd);

	return 0;
}
