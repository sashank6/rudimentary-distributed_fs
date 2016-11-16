#include <iostream>
#include <fstream>
#include <string>
#include "Test.pb.h"

using namespace std;

int main() {

	Test test;
	test.set_name("Test Protobuf");
	fstream output("test.txt", ios::out | ios::trunc | ios::binary);

	if(!test.SerializeToOstream(&output))
		cout<<"Error in serializing"<<endl;


	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}
