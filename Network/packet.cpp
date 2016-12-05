#include "packet.h"
#include "sysinfo.h"
#include "fileops.h"
#include<iostream>
void process_packet(Packet packet, STRING ipaddr) {
	int flag = packet.flag();
	switch (flag) {

	case SYSINFO:
		process_sysinfo(packet, ipaddr);
		break;
	case CALLBACK: {
		Callback callback = packet.callback();
		switch (callback.op()) {
		case WRITE_FILE:
			if (callback.success()) {
				//nodes.at(ipaddr).disksize -= callback.filesize;
			} else {
				// fail or retry
			}
			break;

		default:
			break;
		}
		break;
	}
	case WRITE_FILE:{
		create_file(packet.filedata());
		break;
	}
	case CLIENT_FILE:{
		FileData filedata=packet.filedata();
		std::cout<<filedata.data()<<std::endl;
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

}
