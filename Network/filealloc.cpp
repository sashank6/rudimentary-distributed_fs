#include "filealloc.h"
#include "errors.h"
#include<unordered_map>
//std::unordered_map<std::string, filerecord> fat;
void update_fat(filerecord record) {
	//fat[record.filename] = record;
	write_fat(record);
}
void write_fat(filerecord record) {
	FILE *fp = fopen(FAT_FILE, "a");
	if (fp == NULL)
		handle_error("Unable to open FAT file");
	std::string rec_str=filerec_tostring(record);
	fprintf(fp,"%s\n",rec_str.c_str());
	fclose(fp);

}
std::string filerec_tostring(filerecord record) {
	std::string rec = "";
	rec += record.filename + " ";
	rec += record.host + " ";
	rec += std::to_string(record.size);
	return rec;
}
void getFileIP(std::string filename){
	std::string ip;
	FILE *fp = fopen(FAT_FILE, "r");
	if (fp == NULL)
		handle_error("Unable to open FAT file");
	char filename_buf[1024];
	char ip_buf[1024];
	char size_buf[1024];
	while(!feof(fp)){
	fscanf(fp,"%s",filename_buf);
	fscanf(fp,"%s",ip_buf);
	fscanf(fp,"%s",size_buf);
	if(std::string(filename_buf)==filename){
		ip=std::string(ip_buf);
		break;
	}
	}
	std::cout<<ip<<std::endl;
	fclose(fp);
}
