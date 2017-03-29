#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFERSIZE 100
int main(int argc, char *argv[]) {
	int i;
	char array[BUFFERSIZE];
	if (argc < 2) {
		printf("no args given");
		exit(1);
	}
	printf("Argument given: %c\n", *argv[1]);

	/*
	printf("Enter a phrase: \n");
	scanf("%s", &array);
	*/
	
	fgets (array, BUFFERSIZE, stdin);

	
	for ( i = 0; i < BUFFERSIZE; i++ ) { /* loop through the phrase */
		if (array[i] ==  *argv[1]) /* if the current letter matches the arg */
			array[i] = '\n'; /* swap the mf */

		
	}

	printf(array);
	
	return 0;	
}