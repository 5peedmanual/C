#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	char 	buffer[100];
	pid_t 	pid;
	int	status;

	printf("%");
	while (fgets(buffer, 100, stdin) != NULL)
	{
		if (buffer[strlen(buffer) - 1] == '\n')
			buffer[strlen(buffer) - 1] = 0;
		if ((pid = fork()) < 0)
	       	{
			perror("forking");
			exit(-1);
		} 
		else if (pid == 0) 
		{
			execlp(buffer, buffer, (char *) 0);

