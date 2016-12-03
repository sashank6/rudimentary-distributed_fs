#include "packet.h"
#include "sysinfo.h"
void process_packet(Packet packet, STRING ipaddr) {
	int flag = packet.flag();
	switch (flag) {

	case SYSINFO:
		process_sysinfo(packet, ipaddr);
		break;
	case CALLBACK: {
		Callback callback = packet.callback();
		switch (callback.op()) {
		case WRITE_FILE:
			if (callback.success()) {
				//nodes.at(ipaddr).disksize -= callback.filesize;
			} else {
				// fail or retry
			}
			break;
		case READ_FILE:
			if (callback.success()) {
				if (callback.block() == 0) {
					// whole file
				} else {
					// TODO handle striped file read
				}
			}
			break;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}

}
