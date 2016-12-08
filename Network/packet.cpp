#include "packet.h"
#include "sysinfo.h"
#include "fileops.h"
#include "../Apps/localfileops.h"
#include "serialization.h"
#include "filealloc.h"
#include<iostream>
std::string process_packet(Packet packet, STRING ipaddr) {
	std::string rtr;
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
	case FILE_REQUEST:{
		std::cout<<"Read request"<<std::endl;
		FileRequest request = packet.filerequest();
		std::string file_request_ack =fileRequestAck(request.filename());
		rtr=file_request_ack;
		break;
	}
	case UPDATE_FILE_LIST:{
		FileList files=packet.filelist();
		for(int i=0;i<files.filename_size();i++){
			filerecord record;
			record.filename = files.filename(i);
			record.host=ipaddr;
			record.size=1;
	    	update_fat(record);
		}
		rtr=genAck(1);
		break;
	}
	case READ_FILE:{
		FileRequest request = packet.filerequest();
		std::string data = read_file(request.filename());
		rtr = genDataPacket(request.filename(),data);
		break;
	}

	default:
		break;
	}
	return rtr;

}

std::string genAck(int status){
	Packet packet;
	Ack *ack(new Ack);
	ack->set_status(status);
	packet.set_allocated_ack(ack);
	packet.set_flag(ACK_PACKET);
	std::string serialized_str = serialize(packet);
	return serialized_str;
}

int process_ack(Packet packet,STRING ipaddr){
	int result=0;
	int flag = packet.flag();
		switch (flag) {

		case ACK_PACKET:{
			result = packet.ack().status();
			break;
		}

		case FILE_RECORD:{
			result=1;
			break;
		}
		default:
			break;
		}

		return result;
}

std::string fileRequestAck(std::string filename){
	filerecord record = getFileRecord(filename);
	Packet packet;
	if(record.size==-1){
		Ack *ack(new Ack);
		ack->set_status(-1);
		packet.set_allocated_ack(ack);
		packet.set_flag(ACK_PACKET);
	}else{
		packet.set_flag(FILE_RECORD);
		FileRecord *filerecord(new FileRecord);
		filerecord->set_filename(record.filename);
		filerecord->set_host(record.host);
		filerecord->set_size(1);
		packet.set_allocated_filerecord(filerecord);
	}
	return serialize(packet);
}
std::string genDataPacket(std::string filename,std::string data){
	Packet packet;
	FileData *filedata(new FileData);
	filedata->set_filename(filename);
	filedata->set_data(data);
	packet.set_allocated_filedata(filedata);
	packet.set_flag(FILE_DATA);
	return serialize(packet);
}


