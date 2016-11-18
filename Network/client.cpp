#include "ports.h"
#include "connections.h"
#include "errors.h"
#include "Packet.pb.h"
#include "serialization.h"

using namespace std;

int main() {

	Packet packet;
	packet.set_flag(1);

	send_message("192.168.1.115", SERVER_CONNECT_PORT, packet);

	return 0;

}
