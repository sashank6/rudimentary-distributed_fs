#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
void handle_error(char *error) {
	printf("Error: %s Reason: %s\n", error, strerror(errno));
	exit (EXIT_FAILURE);
}
