#include "Packet.pb.h"
#include "sysinfo.h"
#define SYSINFO 1
#define WRITE_FILE 2
#define READ_FILE 3
#define CALLBACK 4
void process_packet(Packet packet,string ipaddress);
