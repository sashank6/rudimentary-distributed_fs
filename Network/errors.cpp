void handle_error(char *s) {
	printf("Error: %s Reason: %s\n", s, strerror(errno));
	exit (EXIT_FAILURE);
}
