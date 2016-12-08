#include "Packet.pb.h"
#include "types.h"
#define SYSINFO 1
#define WRITE_FILE 2
#define READ_FILE 3
#define CALLBACK 4
#define CLIENT_FILE 5
#define ACK_PACKET 6
#define FILE_RECORD 7
#define UPDATE_FILE_LIST 8
#define FILE_REQUEST 9
#define FILE_DATA 10
std::string process_packet(Packet packet,STRING ipaddress);
int process_ack(Packet packet,STRING ipadress);
std::string genAck(int status);
std::string fileRequestAck(std::string filename);
std::string genDataPacket(std::string filename,std::string data);
