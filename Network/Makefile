CC = g++ -Wall -std=c++11
CCPI = g++ -Wall -std=c++11
RUNTIME_LIBS = -lprotobuf
PROTOC=protoc
PROTOFILES = Packet.proto
HELPERS = errors.cpp connections.cpp Packet.pb.cc serialization.cpp packet.cpp sysinfo.cpp fileops.cpp filealloc.cpp ../Apps/localfileops.cpp

all: compile
pi: compilepi

pre-compile:
	$(PROTOC) --cpp_out=. $(PROTOFILES)
	
compile: pre-compile
	$(CC) client.cpp $(HELPERS) -o client $(RUNTIME_LIBS)
	$(CC) server.cpp $(HELPERS) -o server $(RUNTIME_LIBS)
compilepi: pre-compile
	$(CCPI) client.cpp $(HELPERS) -o client $(RUNTIME_LIBS)
	$(CCPI) server.cpp $(HELPERS) -o server $(RUNTIME_LIBS)
		
	