#include "ports.h"
#include "connections.h"
#include "errors.h"
#include "Packet.pb.h"
#include "serialization.h"
#include "fileops.h"
#include<iostream>

int main() {

//	Packet handshake_packet;
//	handshake_packet.set_flag(1);
//	SystemInformation *sysinfo(new SystemInformation);
//	sysinfo->set_port(CLIENT_PORT);
//	sysinfo->set_disksize(1000);
//	handshake_packet.set_allocated_sysinfo(sysinfo);
//	int result=send_message(SERVER_ADDR, SERVER_CONNECT_PORT, handshake_packet);
	 Packet pck=getFileList();
	 int result=send_message(SERVER_ADDR,SERVER_CONNECT_PORT,pck);
	//open_socket(CLIENT_PORT);


	return 0;

}
