#include "Packet.pb.h"
#include<set>
void create_file(FileData filedata);
std::string read_file(std::string name);
void send_file(std::string filename,std::string data);
Packet getFileList();
std::set<std::string> getLocalFileList();
