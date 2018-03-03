#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char	buf1[] = "abcdefghij";
char 	buf2[] = "ABCDEFGIJ";

int
main(void)
{
	int	fd;

	if ((fd = creat("file.hole", FILE_MODE)) < 0)
		perror("Creating file");
	
	if (write(fd, buf1, 10) != 10)
		perror("Writing to file");
	// offset now = 10 
	
	if (lseek(fd, 16384, SEEK_SET) == -1)
		perror("Seeking");
	// offset now = 16384
	
	if(write(fd, buf2, 10) != 10)
		perror("Writing to file");
	// offset now = 16394
	
	return 0;
}
	
