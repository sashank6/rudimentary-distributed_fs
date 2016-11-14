#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<errno.h>
#include <netinet/in.h>

#define PORT 34343

void handle_error(char *s) {
	printf("Error: %s Reason: %s\n", s, strerror(errno));
	exit(EXIT_FAILURE);
}

int main() {

	int socket_fd;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		handle_error("Socket Opening Error");

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);

	if (bind(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))
			== -1)
		handle_error("Bind error");

	if (listen(socket_fd, 5) == -1)
		handle_error("listen error");

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int con_fd;
	do {
		con_fd = accept(socket_fd, (struct sockaddr *) &client_addr,
				&client_len);
		printf("IP address of client is: %s\n", inet_ntoa(client_addr.sin_addr));
	}while(con_fd!=-1);

	if (con_fd == -1)
	handle_error("Accept Error");

	close(con_fd);
	close(socket_fd);

	return 0;
}
