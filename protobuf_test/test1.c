#include <stdio.h>
#include <stdlib.h>
#include "SystemInfo.pb-c.h"

int main(int argc, const char * argv[]) {
	SystemInfo msg = SYSTEM_INFO__INIT; // AMessage
	void *buf;                     // Buffer to store serialized data
	unsigned len;                  // Length of serialized data



	msg.foldersize = 23;
	msg.port = 34343;
	len = system_info__get_packed_size(&msg);

	buf = malloc(len);
	system_info__pack(&msg, buf);

	fprintf(stderr, "Writing %d serialized bytes\n", len); // See the length of message
	fwrite(buf, len, 1, stdout); // Write to stdout to allow direct command line piping

	free(buf); // Free the allocated serialized buffer
	return 0;
}
