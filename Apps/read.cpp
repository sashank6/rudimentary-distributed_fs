#include "../Network/Packet.pb.h"
#include "../Network/connections.h"
#include "../Network/packet.h"
#include "../Network/ports.h"

int main(){
	Packet packet;
	packet.set_flag(READ_FILE);
	FileRequest *filerequest(new FileRequest);
	filerequest->set_filename("nodes.h");
	packet.set_allocated_filerequest(filerequest);
	send_message("192.168.1.90",CLIENT_PORT,packet);
	return 0;
}
