#include "sysinfo.h"
void process_sysinfo(Packet packet, string ipaddr) {

	SystemInformation sysinfo = packet.sysinfo();
	int port = sysinfo.port();
	int disksize = sysinfo.disksize();
	Sysinfo sysinfo_struct;
	sysinfo_struct.ipaddress = ipaddr;
	sysinfo_struct.port = port;
	sysinfo_struct.disksize = disksize;

}
