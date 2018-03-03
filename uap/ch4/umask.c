#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

// Creates two files:
// one with umask of 0 and one with umask that disables all the group
// and other permission bits


int main(void)
{
	umask(0);
	if (creat("foo", RWRWRW) < 0)
		perror("creating file");
	umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);	
	if (creat("bar", RWRWRW) < 0)
		perror("creating second file");
	exit(0);
}
