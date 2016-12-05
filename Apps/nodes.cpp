#include "../Network/sharedmem.h"
#include "../Network/Packet.pb.h"
#include "../Network/packet.h"
#include "../Network/connections.h"

Sysinfo getBestNode() {
	std::unordered_map<STRING,Sysinfo> nodes_dict=read_shm_nodes();
	Sysinfo best_node;
	int disksize=0;
	std::unordered_map<STRING,Sysinfo> :: iterator it;
	for(it=nodes_dict.begin();it!=nodes_dict.end();++it) {
		if(it->second.disksize > disksize)
		best_node=it->second;
	}
	return best_node;
}

void write_to_node(Sysinfo node, std::string filename, std::string data) {
	Packet packet;
	packet.set_flag(WRITE_FILE);
	FileData *filedata(new FileData);
	filedata->set_filename(filename);
	filedata->set_data(data);
	packet.set_allocated_filedata(filedata);
	char *ipaddr = new char[node.ipaddress.length() + 1];
	strcpy(ipaddr, node.ipaddress.c_str());
	send_message(ipaddr, node.port, packet);
	delete[] ipaddr;
}
