CC = c++
RUNTIME_LIBS = -lprotobuf
PROTOC=protoc
PROTOFILES = Packet.proto

all: compile

pre-compile:
	$(PROTOC) --cpp_out=. $(PROTOFILES)
	
compile: pre-compile
	$(CC) client.cpp connections.cpp errors.cpp Packet.pb.cc serialization.cpp -o client $(RUNTIME_LIBS)
	$(CC) server.cpp connections.cpp errors.cpp Packet.pb.cc serialization.cpp -o server $(RUNTIME_LIBS)
		
	