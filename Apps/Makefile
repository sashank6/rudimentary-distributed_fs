CC = g++ -Wall -std=c++11 -I /usr/local/Cellar/boost/
CCPI = g++ -Wall -std=c++11 -I /usr/local/Cellar/boost_1_62_0/ -lrt
RUNTIME_LIBS = -lprotobuf
PROTOC=protoc
PROTOFILES = Packet.proto
HELPERS = errors.cpp connections.cpp Packet.pb.cc serialization.cpp packet.cpp sysinfo.cpp fileops.cpp sharedmem.cpp
WRITE = write.cpp
WRITE_HELPERS=../Network/sharedmem.cpp nodes.cpp ../Network/Packet.pb.cc ../Network/connections.cpp ../Network/fileops.cpp ../Network/sysinfo.cpp ../Network/packet.cpp ../Network/serialization.cpp ../Network/errors.cpp localfileops.cpp ../Network/filealloc.cpp 

write:
	$(CC) $(WRITE) $(WRITE_HELPERS) -o write $(RUNTIME_LIBS)
writepi:
	$(CCPI) $(WRITE) $(WRITE_HELPERS) -o write	$(RUNTIME_LIBS)
		
	