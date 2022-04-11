#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

void	*rngalloc(size_t size)
{
	int fd = open("/dev/urandom", O_RDONLY);
	char buffer[1];
	int r;

	read(fd, buffer, 1);
	close(fd);

	r = (unsigned char)buffer[0];
	printf("%d\n", r);
	if (r != 0)
		return malloc(size);
	errno = ENOMEM;
	return NULL;
}