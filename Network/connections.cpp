#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include "errors.h"
#include "Packet.pb.h"
void open_socket(unsigned int port) {
	int socket_fd;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		handle_error("Socket Opening Error");

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

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
		char ipaddr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(client_addr.sin_addr), ipaddr, INET_ADDRSTRLEN);
		printf("IP address of client is: %s\n", ipaddr);
	} while (con_fd != -1);

	if (con_fd == -1)
		handle_error("Accept Error");

	close(con_fd);
	close(socket_fd);
}

void send_message(char *hostname, unsigned int port, Packet packet) {
	int socket_fd;
	struct sockaddr_in serv_addr;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		handle_error("Socket Opening Error");

	struct hostent *server;
	server = gethostbyname(hostname);
	if (server == NULL)
		handle_error("No valid host");

	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(port);

	if (connect(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))
			== -1)
		handle_error("Connection Error");
	close(socket_fd);
}

