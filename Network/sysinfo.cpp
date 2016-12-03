#include"Packet.pb.h"
#include "packet.h"
#include "sysinfo.h"
#include "connections.h"
#include<iterator>
static std::unordered_map<STRING, Sysinfo> nodes;
//Processes packet to retrieve slave-device information and updates in in-memory dictionary
void process_sysinfo(Packet packet, STRING ipaddr) {

	SystemInformation sysinfo = packet.sysinfo();
	int port = sysinfo.port();
	int disksize = sysinfo.disksize();
	Sysinfo sysinfo_struct;
	sysinfo_struct.ipaddress = ipaddr;
	sysinfo_struct.port = port;
	sysinfo_struct.disksize = disksize;
	addNode(sysinfo_struct);
	displayNodes();
}
//Adds node to node dictionary
void addNode(Sysinfo sysinfo) {
	nodes[sysinfo.ipaddress] = sysinfo;
	Packet packet;
	packet.set_flag(WRITE_FILE);
	FileData *filedata(new FileData);
	filedata->set_filename("test");
	filedata->set_data("This is test data");
	packet.set_allocated_filedata(filedata);
	char *ipaddr = new char[sysinfo.ipaddress.length() + 1];
	strcpy(ipaddr, sysinfo.ipaddress.c_str());
	send_message(ipaddr,sysinfo.port,packet);
	delete[] ipaddr;
}

void displayNodes() {
	printf("List of All Slave-devices:\n");
	std::unordered_map<STRING, Sysinfo>::iterator it;
	for (it = nodes.begin(); it != nodes.end(); ++it) {
		printf("IP: %s PORT: %d SPACEAVBL %d\n", it->first.c_str(),
				it->second.port, it->second.disksize);
	}

}

