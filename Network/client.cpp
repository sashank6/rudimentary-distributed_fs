#include "ports.h"
#include "connections.h"
#include "errors.h"
#include "Packet.pb.h"

using namespace std;

int main() {

	Packet packet;

	send_message("192.168.1.115", SERVER_CONNECT_PORT, packet);

	return 0;

}
