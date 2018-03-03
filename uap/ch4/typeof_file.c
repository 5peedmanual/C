#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void main(int argc, char *argv[])
{
	char 		buffer[1024];
	DIR 		*dir_ptr;
	struct dirent 	*dp;
	struct stat	ss;
	char		*ptr;


	dir_ptr = opendir(argv[1]);

	if(argc < 1) {
		printf("usage: ./a.out <directory>\n");
		exit(0);
	}
      
	if (dir_ptr != NULL) {
		while(dp  = readdir(dir_ptr))
		{

			// printf("%s\n", dp->d_name);
			strcpy(buffer, argv[1]);
			strcat(buffer, dp->d_name);

			if (lstat(buffer, &ss) < 0) {
				perror("lstat error");
					continue;
			}

			printf("%-40s:\t\t ", buffer);
			if (S_ISREG(ss.st_mode))
				ptr = "Regular file";
			else if (S_ISDIR(ss.st_mode))
				ptr = "Directory file";
			else if (S_ISCHR(ss.st_mode))
				ptr = "Character special file";
			else if (S_ISBLK(ss.st_mode))
				ptr = "Block special file";
			else if (S_ISFIFO(ss.st_mode))
				ptr = "FIFO type file";
			else if (S_ISLNK(ss.st_mode))
				ptr = "Symbolic link file";
			else if (S_ISSOCK(ss.st_mode))
				ptr = "Socket file";
			else
				ptr = "unknown type of file";
			printf("%s\n", ptr);

		}
		(void) closedir(dir_ptr);

	} else {
		perror("Couldn't open directory");
	}
}

