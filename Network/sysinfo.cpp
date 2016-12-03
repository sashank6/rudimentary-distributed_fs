#include "sysinfo.h"
#include<iterator>
static std::unordered_map<STRING, Sysinfo> deviceList;
//Processes packet to retrieve slave-device information and updates in in-memory dictionary
void process_sysinfo(Packet packet, STRING ipaddr) {

	SystemInformation sysinfo = packet.sysinfo();
	int port = sysinfo.port();
	int disksize = sysinfo.disksize();
	Sysinfo sysinfo_struct;
	sysinfo_struct.ipaddress = ipaddr;
	sysinfo_struct.port = port;
	sysinfo_struct.disksize = disksize;
	addDevice(sysinfo_struct);
	displayDevices();
}

void addDevice(Sysinfo sysinfo) {
	deviceList[sysinfo.ipaddress] = sysinfo;
}

void displayDevices() {
	printf("List of All Slave-devices:\n");
	std::unordered_map<STRING, Sysinfo>::iterator it;
	for (it = deviceList.begin(); it != deviceList.end(); ++it) {
		printf("IP: %s PORT: %d SPACEAVBL %d\n", it->first.c_str(),
				it->second.port, it->second.disksize);
	}
}

