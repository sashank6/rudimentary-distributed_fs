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
void process_sysinfo(Packet packet, STRING ipaddr);
void addDevice(Sysinfo info);
void displayDevices();
