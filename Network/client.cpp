#include "ports.h"
#include "connections.h"
#include "errors.h"
#include "Packet.pb.h"
#include "serialization.h"

using namespace std;

int main() {

	Packet handshake_packet;
	handshake_packet.set_flag(1);
	SystemInformation sysinfo;
	sysinfo.set_port(CLIENT_PORT);
	sysinfo.set_disksize(1000);
	handshake_packet.set_allocated_sysinfo(&sysinfo);

	send_message("192.168.1.115", SERVER_CONNECT_PORT, handshake_packet);

	return 0;

}
