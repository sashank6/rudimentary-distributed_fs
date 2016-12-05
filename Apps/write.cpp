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
#include "../Network/sharedmem.h"
int main() {
	using namespace boost::interprocess;
	shared_memory_object shm(open_only, SHM_NODE, read_only);
	mapped_region region(shm, read_only);
	struct Sysinfo_shm *mem = static_cast<Sysinfo_shm*>(region.get_address());
	for (std::size_t i = 0; i < region.get_size() / sizeof(Sysinfo_shm); ++i) {
		std::cout << mem[i].port << "," << mem[i].filesize<<std::endl;
	}
	return 0;
}

