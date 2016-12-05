#include "sharedmem.h"

void write_shm_nodes(std::unordered_map<STRING,Sysinfo> nodes) {

	using namespace boost::interprocess;
	struct shm_remove {
		shm_remove() {
			shared_memory_object::remove(SHM_NODE);
		}
	}remover;

	unsigned int node_size=nodes.size();
	shared_memory_object shm(create_only, SHM_NODE, read_write);
	shm.truncate(node_size*sizeof(Sysinfo_shm));
	mapped_region region(shm, read_write);
	struct Sysinfo_shm *node=static_cast<Sysinfo_shm*>(region.get_address());
	std::unordered_map<STRING,Sysinfo>::iterator it;
	int count=0;
	for(it=nodes.begin();it!=nodes.end();++it) {
		Sysinfo buf=it->second;
		strcpy(node[count].ipaddr,buf.ipaddress.c_str());
		node[count].port=buf.port;
		node[count].filesize=buf.disksize;
		node[count].isAlive=buf.isAlive;
	}

}

std::unordered_map<STRING,Sysinfo> read_shm_nodes() {
	std::unordered_map<STRING,Sysinfo> nodes_dict;
	using namespace boost::interprocess;
	shared_memory_object shm(open_only, SHM_NODE, read_only);
	mapped_region region(shm, read_only);
	struct Sysinfo_shm *mem = static_cast<Sysinfo_shm*>(region.get_address());
	for (std::size_t i = 0; i < region.get_size() / sizeof(Sysinfo_shm); ++i){
			Sysinfo buf;
			buf.ipaddress=std::string(mem[i].ipaddr);
			buf.port=mem[i].port;
			buf.isAlive=mem[i].isAlive;
			buf.disksize=mem[i].filesize;
			nodes_dict[buf.ipaddress]=buf;
	}
	return nodes_dict;
}



