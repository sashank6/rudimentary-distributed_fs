/*
 *
 */
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include "nodes.h"
#include<iostream>
int main() {
	Sysinfo best_node=getBestNode();
	write_to_node(best_node,"test1","This is a test data");
	return 0;
}

