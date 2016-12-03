#include "serialization.h"

STRING serialize(Packet packet) {
	STRING data;
	if (!packet.SerializeToString(&data))
		handle_error("serialization error");
	return data;
}

Packet deserialize(STRING data) {
	Packet packet;
	if (!packet.ParseFromString(data))
		handle_error("deserialization error");
	return packet;
}
