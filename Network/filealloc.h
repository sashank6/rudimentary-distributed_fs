#include<iostream>
#define FAT_FILE "../data/fatdata"
struct filerecord{
	std::string filename;
	std::string host;
	int size;
};
void update_fat(filerecord record);
void write_fat(filerecord record);
std::string filerec_tostring(filerecord record);
filerecord getFileRecord(std::string filename);
