#include "connections.h"
#include "packet.h"
#include<iostream>

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

		STRING recd_data="";

		char buf[3072];
		memset(buf, 0, strlen(buf));
		int read_size;
		while( (read_size = recv(con_fd , buf , 3072 , 0)) > 0 )
		    {
		        recd_data+=std::string(buf);
		    }

		shutdown(con_fd,SHUT_RD);
		Packet packet=deserialize(recd_data);
		printf("Read data\n");
		std::string ack = process_packet(packet,std::string(ipaddr));
		if(send(con_fd,ack.c_str(),ack.length(),0)<0){
				printf("Failed send\n");
		}

		close(con_fd);

	}

	if (con_fd == -1)
		handle_error("Accept Error");
	}

	close(socket_fd);
}

int send_message(char *hostname, unsigned int port, Packet packet) {

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

	STRING serialized_data = serialize(packet);
	if(send(socket_fd_rec,serialized_data.c_str(),serialized_data.length(),0)<0){
		printf("Failed send\n");
	}
	shutdown(socket_fd_rec,SHUT_WR);
	printf("Message Sent\n");
	STRING recd_data="";
	char buf[3072];
			memset(buf, 0, strlen(buf));
			int read_size;
			while( (read_size = recv(socket_fd_rec , buf , 3072 , 0)) > 0 )
			    {
			        recd_data+=std::string(buf);
			    }
	Packet ack= deserialize(recd_data);
	int result = process_ack(ack,std::string(hostname));

	close(socket_fd_rec);
	return result;
}

