#include "connections.h"
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

		string recd_data;
		FILE *read_stream = fdopen(con_fd, "r");
		char str[1024];
		while (fgets(str, 1024, read_stream) != NULL) {
			recd_data += string(str);
		}

		Packet packet = deserialize(recd_data);
		printf("%d\n", packet.flag());
		fclose(read_stream);

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

	FILE *write_stream = fdopen(socket_fd, "w");
	string serialized_data = serialize(packet);
	fprintf(write_stream, "%s", serialized_data.c_str());

	fclose(write_stream);
	close(socket_fd);
}

