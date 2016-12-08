#include "../Network/Packet.pb.h"
#include "../Network/connections.h"
#include "../Network/packet.h"
#include "../Network/ports.h"
#include "../Network/errors.h"
#include "../Network/filealloc.h"
#include "../Network/serialization.h"
#include "localfileops.h"
#include<iostream>

int main(int argc,char*argv[]){
	if(argc<2){
		handle_error("Invalid number of arguments");
	}
	Packet packet;
	packet.set_flag(FILE_REQUEST);
	FileRequest *filerequest(new FileRequest);
	filerequest->set_filename(std::string(argv[1]));
	packet.set_allocated_filerequest(filerequest);
	Packet pck = send_message(SERVER_ADDR,SERVER_CONNECT_PORT,packet);
	int result = process_ack(pck,SERVER_ADDR);
	if(result==1){
		FileRecord record = pck.filerecord();
		Packet pack;
		pack.set_flag(READ_FILE);
		FileRequest *request(new FileRequest);
		request->set_filename(record.filename());
		pack.set_allocated_filerequest(request);
		char adr[record.host().length()];
		strcpy(adr,record.host().c_str());
		Packet data = send_message(adr,CLIENT_PORT,pack);
		writeFile(data.filedata().data(),record.filename());
	}else{
		std::cout<<"No such file exists"<<std::endl;
	}


	return 0;
}
