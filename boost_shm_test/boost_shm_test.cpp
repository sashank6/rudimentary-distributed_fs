#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>

struct item {
	int a;
	int b;
	int c;
};

int main(int argc, char *argv[]) {
	using namespace boost::interprocess;

	if (argc == 1) {  //Parent process
		//Remove shared memory on construction and destruction
		struct shm_remove {
			shm_remove() {
				shared_memory_object::remove("MySharedMemory");
			}
			~shm_remove() {
				shared_memory_object::remove("MySharedMemory");
			}
		} remover;

		//Create a shared memory object.
		shared_memory_object shm(create_only, "MySharedMemory", read_write);

		int arraysize = 2;

		unsigned int totsize = arraysize * sizeof(item);
		std::cout << totsize << std::endl;

		//Set size
		shm.truncate(totsize);

		//Map the whole shared memory in this process
		mapped_region region(shm, read_write);

		//Write all the memory to 1
		struct item *x =static_cast<item*>(region.get_address());
		x[0].a=1111;
		x[0].b=2222;
		x[0].c=3333;
		x[1].a=4444;
		x[1].b=5555;
		x[1].c=6666;

		//Launch child process
		std::string s(argv[0]);
		s += " child ";
		if (0 != std::system(s.c_str()))
			return 1;
	} else {
		//Open already created shared memory object.
		shared_memory_object shm(open_only, "MySharedMemory", read_only);

		//Map the whole shared memory in this process
		mapped_region region(shm, read_only);

		//Check that memory was initialized to 1
		int count = 0;
		struct item *mem = static_cast<item*>(region.get_address());
		for (std::size_t i = 0; i < region.get_size()/sizeof(item); ++i) {
			std::cout<<mem[i].a<<","<<mem[i].b<<","<<mem[i].c<<std::endl;
			  //Error checking memory
		}
//		std::cout << count << std::endl;
	}
	return 0;
}
