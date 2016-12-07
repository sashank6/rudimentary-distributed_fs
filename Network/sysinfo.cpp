#include"Packet.pb.h"
#include "packet.h"
#include "connections.h"
#include "sharedmem.h"
#include<iterator>
static std::unordered_map<STRING, Sysinfo> nodes;
//Processes packet to retrieve slave-device information and updates in in-memory dictionary
bool process_sysinfo(Packet packet, STRING ipaddr) {

	SystemInformation sysinfo = packet.sysinfo();
	int port = sysinfo.port();
	int disksize = sysinfo.disksize();
	Sysinfo sysinfo_struct;
	sysinfo_struct.ipaddress = ipaddr;
	sysinfo_struct.port = port;
	sysinfo_struct.disksize = disksize;
	addNode(sysinfo_struct);
	displayNodes();
	return true;
	//write_shm_nodes(nodes);
}
//Adds node to node dictionary
void addNode(Sysinfo sysinfo) {
	nodes[sysinfo.ipaddress] = sysinfo;
}

void displayNodes() {
	printf("List of All Slave-devices:\n");
	std::unordered_map<STRING, Sysinfo>::iterator it;
	for (it = nodes.begin(); it != nodes.end(); ++it) {
		printf("IP: %s PORT: %d SPACEAVBL %d\n", it->first.c_str(),
				it->second.port, it->second.disksize);
	}

}

