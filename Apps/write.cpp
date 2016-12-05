/*
 * Packet packet;
 packet.set_flag(WRITE_FILE);
 FileData *filedata(new FileData);
 filedata->set_filename("test");
 filedata->set_data("This is test data");
 packet.set_allocated_filedata(filedata);
 char *ipaddr = new char[sysinfo.ipaddress.length() + 1];
 strcpy(ipaddr, sysinfo.ipaddress.c_str());
 send_message(ipaddr,sysinfo.port,packet);
 delete[] ipaddr;
 */
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include "nodes.h"
#include<iostream>
int main() {
	std::string ip=getBestNode();
	std::cout<<ip<<std::endl;

	return 0;
}

