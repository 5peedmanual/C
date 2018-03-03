#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// int chmod(const char *pathname, mode_t mode)

int main(void) 
{
	struct stat sb;
	/* turn on set-group-ID and turn off group-exe */
	if (stat("foo", &sb) < 0)
		perror("stat error on foo");
	if (chmod("foo", (sb.st_mode & ~S_IXGRP) | S_ISGID) < 0)
		perror("chmod error on foo");
	/* set absolute mode to "rw-r--r--" */
	if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
		perror("chmod error on bar");
	exit(0);
}
	
