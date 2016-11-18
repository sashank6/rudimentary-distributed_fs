#include "serialization.h"

string serialize(Packet packet) {
	string data;
	if (!packet.SerializeToString(&data))
		handle_error("serialization error");
	return data;
}

Packet deserialize(string data) {
	Packet packet;
	if (!packet.ParseFromString(data))
		handle_error("deserialization error");
	return packet;
}
