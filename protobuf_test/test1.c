#include <stdio.h>
#include <stdlib.h>
#include "SystemInfo.pb-c.h"

int main(int argc, const char * argv[]) {
	SystemInfo msg = SYSTEM_INFO__INIT;
	void *buf;
	unsigned len;

	msg.foldersize = 23;
	msg.port = 34343;
	len = system_info__get_packed_size(&msg);

	buf = malloc(len);
	system_info__pack(&msg, buf);

	fprintf(stderr, "Writing %d serialized bytes\n", len);
	fwrite(buf, len, 1, stdout); //


	free(buf);
	return 0;
}
