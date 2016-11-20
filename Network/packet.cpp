#include "packet.h"
void process_packet(Packet packet, string ipaddr) {
	int flag = packet.flag();
	switch (flag) {

	case SYSINFO:
		process_sysinfo(packet,ipaddr);
		break;
	default:
		break;
	}

}
