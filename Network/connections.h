#include "Packet.pb.h"
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
#include "serialization.h"
#include <string>
void open_socket(unsigned int);
bool send_message(char *hostname, unsigned int port, Packet packet);
void open_client_sock(unsigned int);
