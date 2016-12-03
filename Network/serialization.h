#include "Packet.pb.h"
#include "errors.h"
#include "types.h"
std::string serialize(Packet packet);
Packet deserialize(std::string data);

