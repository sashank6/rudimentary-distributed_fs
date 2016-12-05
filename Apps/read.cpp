#include "../Network/Packet.pb.h"
#include "../Network/connections.h"
#include "../Network/packet.h"
#include "../Network/ports.h"
#include "../Network/errors.h"
#include "../Network/filealloc.h"

int main(int argc,char*argv[]){
	if(argc<2){
		handle_error("Invalid number of arguments");
	}
	Packet packet;
	packet.set_flag(READ_FILE);
	FileRequest *filerequest(new FileRequest);
	filerequest->set_filename(std::string(argv[1]));
	packet.set_allocated_filerequest(filerequest);
	std::string fileIP=getFileIP(std::string(argv[1]));
	char fileip[fileIP.length()+1];
	strcpy(fileip,fileIP.c_str());
	send_message(fileip,CLIENT_PORT,packet);
	return 0;
}
