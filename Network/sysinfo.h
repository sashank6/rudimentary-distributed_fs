#include "Packet.pb.h"
#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
struct Sysinfo {
	string ipaddress;
	int port;
	int disksize;
	bool isAlive;
};
void process_sysinfo(Packet packet, string ipaddr);
