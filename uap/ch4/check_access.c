#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: a.out <pathname>");
		exit(1);
	}

	if (access(argv[1], R_OK) < 0)
		perror("access read error");
	else
		printf("read acess OK\n");

	if (access(argv[1], W_OK) < 0)
		perror("acess write error");
	else
		printf("write permission OK\n");

	if (access(argv[1], X_OK) < 0)
		perror("acess execute error");
	else
		printf("execute permission OK\n");

	if (open(argv[1], O_RDONLY) < 0)
		perror("open error");
	else
		printf("open for reading OK\n");

	exit(0);
}
