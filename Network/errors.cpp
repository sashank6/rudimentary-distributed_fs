#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<iostream>
#include"types.h"
void handle_error(STRING error) {
	printf("Error: %s Reason: %s\n", error.c_str(), strerror(errno));
	exit (EXIT_FAILURE);
}
