#include"fileops.h"
#include "types.h"
#include "globals.h"
#include "errors.h"
#include "../Apps/localfileops.h"
#include "Packet.pb.h"
#include "packet.h"
#include "connections.h"

//Creates a file in data directory
void create_file(FileData filedata) {
	STRING filename = filedata.filename();
	STRING data = filedata.data();
	filename = CLIENT_DATA_PATH + filename;

	FILE *fp = fopen(filename.c_str(),"w");
	if(fp==NULL)
		handle_error("File creation error");
	fprintf(fp,"%s",data.c_str());
	fclose(fp);
}

std::string read_file(std::string filename){
	filename = CLIENT_DATA_PATH + filename;
	std::string data=readFile(filename);
	return data;
}
void send_file(std::string filename,std::string data){
	Packet packet;
	FileData *filedata(new FileData);
	filedata->set_filename(filename);
	filedata->set_data(data);
	packet.set_flag(CLIENT_FILE);
	packet.set_allocated_filedata(filedata);
	send_message("192.168.1.115",34343,packet);
}
