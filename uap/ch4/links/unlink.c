#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/* int link(const char *existingpath, const char *newpath); */
/* int linkat(int efd, const char *existingpath, int nfd, const char *newpath,
		int flag); */

int main(void)
{
	if (open("tmpfile", O_RDWR) < 0) {
		perror("opening tmpfile");
		exit(1);
	}
	if (unlink("tmpfile") < 0) {
		perror("unlinking tmpfile");
		exit(1);
	}
	puts("tmpfile unlinked");
	sleep(15);
	puts("done");
	exit(0);
}
