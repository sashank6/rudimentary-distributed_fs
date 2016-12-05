#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include<unordered_map>
#include"sysinfo.h"
#include "types.h"
#define SHM_NODE "nodedirectory"
struct Sysinfo_shm{
	char ipaddr[15];
	int port;
	int filesize;
	bool isAlive;
};
void write_shm_nodes(std::unordered_map<STRING,Sysinfo> nodes);
std::unordered_map<STRING,Sysinfo> read_shm_nodes();
