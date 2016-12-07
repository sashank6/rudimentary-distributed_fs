#include "packet.h"
#include "sysinfo.h"
#include "fileops.h"
#include "../Apps/localfileops.h"
#include<iostream>
Packet process_packet(Packet packet, STRING ipaddr) {
	Packet rtr;
	int flag = packet.flag();
	switch (flag) {

	case SYSINFO:{
		bool success = process_sysinfo(packet, ipaddr);
		rtr=genAck(success);
		break;
	}
	case WRITE_FILE:{
		create_file(packet.filedata());
		break;
	}
	case CLIENT_FILE:{
		FileData filedata=packet.filedata();
		writeFile(filedata.data(),filedata.filename());
		break;
	}
	case READ_FILE:{

		FileRequest request = packet.filerequest();
		std::string data = read_file(request.filename());
		send_file(request.filename(),data);
		break;
	}

	default:
		break;
	}
	return rtr;

}

Packet genAck(bool status){
	Packet packet;
	Ack *ack(new Ack);
	ack->set_status(status);
	packet.set_allocated_ack(ack);
	return packet;
}


