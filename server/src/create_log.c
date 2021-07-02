#include "server.h"

int create_log() {
	int fd = 0;

	fd = open("userver.log", O_CREAT | O_RDWR | O_APPEND, S_IREAD | S_IWRITE);
	if (fd < 0)
		error_msg("fd");
	return fd;
}