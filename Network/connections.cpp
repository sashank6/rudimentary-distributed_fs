#include "connections.h"
#include "packet.h"

/*
 * TODO: Add function to poll slave-devices and update isAlive in devList
 */


/*
 * TODO:// Separate opening of socket and accepting connections.
 */

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

	for(;;){
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int con_fd;
	while ((con_fd = accept(socket_fd, (struct sockaddr *) &client_addr,
			&client_len)) != -1) {
		char ipaddr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(client_addr.sin_addr), ipaddr, INET_ADDRSTRLEN);
		printf("IP address of client is: %s\n", ipaddr);

		STRING recd_data;
		FILE *read_stream = fdopen(con_fd, "r");
		char str[1024];
		while (fgets(str, 1024, read_stream) != NULL) {
			recd_data += std::string(str);
		}

		Packet packet = deserialize(recd_data);
		std::string ack=process_packet(packet,ipaddr);

		FILE *write_stream = fdopen(con_fd, "w");
		if(write_stream==NULL)
			handle_error("Unable to open write_stream open_sock");
		fprintf(write_stream, "%s", ack.c_str());

		fclose(write_stream);
		close(con_fd);

	}

	if (con_fd == -1)
		handle_error("Accept Error");
	}

	close(socket_fd);
}

bool send_message(char *hostname, unsigned int port, Packet packet) {

	int socket_fd_rec;
	struct sockaddr_in serv_addr;

	socket_fd_rec = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd_rec == -1)
		handle_error("Socket Opening Error");

	struct hostent *server;
	server = gethostbyname(hostname);
	if (server == NULL)
		handle_error("No valid host");

	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(port);

	if (connect(socket_fd_rec, (struct sockaddr *) &serv_addr, sizeof(serv_addr))
						== -1)
			handle_error("Connection Error");

	FILE *write_stream = fdopen(socket_fd_rec, "w");
	STRING serialized_data = serialize(packet);
	fprintf(write_stream, "%s", serialized_data.c_str());

	STRING recd_data;
	FILE *read_stream = fdopen(socket_fd_rec, "r");
	char str[1024];
	while (fgets(str, 1024, read_stream) != NULL) {
		recd_data += std::string(str);
	}

	Packet ack= deserialize(recd_data);
	bool result = process_ack(ack,std::string(hostname));
	fclose(write_stream);
	close(socket_fd_rec);
	return result;
}

