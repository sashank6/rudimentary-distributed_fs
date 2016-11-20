CC = c++
RUNTIME_LIBS = -lprotobuf
PROTOC=protoc
PROTOFILES = Packet.proto
HELPERS = connections.cpp errors.cpp Packet.pb.cc serialization.cpp packet.cpp sysinfo.cpp

all: compile

pre-compile:
	$(PROTOC) --cpp_out=. $(PROTOFILES)
	
compile: pre-compile
	$(CC) client.cpp $(HELPERS) -o client $(RUNTIME_LIBS)
	$(CC) server.cpp $(HELPERS) -o server $(RUNTIME_LIBS)
		
	