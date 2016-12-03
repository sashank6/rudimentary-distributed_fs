#include "Packet.pb.h"
#define SYSINFO 1
#define WRITE_FILE 2
#define READ_FILE 3
#define CALLBACK 4
using namespace std;
void process_packet(Packet packet,string ipaddress);
