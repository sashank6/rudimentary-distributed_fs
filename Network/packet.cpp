#include "packet.h"
#include "sysinfo.h"
void process_packet(Packet packet) {
	int flag = packet.flag();
	switch (flag) {

	case SYSINFO:
		process_sysinfo(packet);
		break;
	default:
		break;
	}

}
