#include "../Network/sharedmem.h"

std::string getBestNode() {
	std::unordered_map<STRING,Sysinfo> nodes_dict=read_shm_nodes();
	std::string ip;
	int disksize=0;
	std::unordered_map<STRING,Sysinfo> :: iterator it;
	for(it=nodes_dict.begin();it!=nodes_dict.end();++it) {
		if(it->second.disksize > disksize)
		ip=it->first;
	}
	return ip;
}
