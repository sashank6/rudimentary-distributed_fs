#include "localfileops.h"
#include "../Network/errors.h"
std::string readFile(std::string filename) {
	FILE *fp = fopen(filename.c_str(), "r");
	if (fp == NULL) {
		handle_error("Unable to open file: " + filename);
	}
	std::string data = "";
	char buf[256];
	while (fgets(buf, 256, fp) != NULL) {
		data += std::string(buf);
	}
	fclose(fp);
	return data;
}
