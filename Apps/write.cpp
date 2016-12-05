/*
 *
 */
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include<iostream>
#include "nodes.h"
#include "localfileops.h"
int main(int argc, char *argv[]) {
	if (argc < 3) {
		std::cout << "Invalid arguments" << std::endl;
	}
	std::string read_file = std::string(argv[1]);
	std::string result_file = std::string(argv[2]);
	std::string data = readFile(read_file);
	std::cout<<data<<std::endl;

//	Sysinfo best_node=getBestNode();
//	write_to_node(best_node,"test1","This is a test data");
	return 0;
}

