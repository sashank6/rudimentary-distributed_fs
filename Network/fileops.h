#include "Packet.pb.h"
void create_file(FileData filedata);
std::string read_file(std::string name);
void send_file(std::string filename,std::string data);
Packet getFileList();
