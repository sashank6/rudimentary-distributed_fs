#include "sysinfo.h"
void process_sysinfo(Packet packet) {

	SystemInformation sysinfo = packet.sysinfo();
	int port = sysinfo.port();
	int filesize = sysinfo.filesize();
	printf("PORT: %d FILESIZE: %d\n", port, filesize);
}
