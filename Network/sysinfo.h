#include "Packet.pb.h"
#include"types.h"
#include<stdio.h>
#include<string>
#include<iostream>
#include<unordered_map>
struct Sysinfo {
	STRING ipaddress;
	int port;
	int disksize;
	bool isAlive;
};
bool process_sysinfo(Packet packet, STRING ipaddr);
void addNode(Sysinfo info);
void displayNodes();
