#include <iostream>
#include <fstream>
#include <string>
#include "Test.pb.h"

using namespace std;
int main() {

	Test test;
	fstream input("test.txt", ios::in | ios::binary);
	if (!test.ParseFromIstream(&input))
		cout << "Error" << endl;
	cout<<test.name()<<endl;

	return 0;
}
