#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	FILE *stdin;
	int i;
	char array[10];

	if (argc < 2) {
		printf("no args given");
		exit(1);
	}
	printf("Argument given: %c\n", *argv[1]);

	/*	
	printf("Enter a phrase: \n");
	scanf("%s", &array);
	*/

    stdin = fopen("file" , "r");
    /* openornah */
    if ( stdin == NULL ) {
        printf("Cant open that\n");
        return 1;
    }

    if ( fgets (array, 10, stdin) != NULL ) { /* if not null proceed */
		for ( i = 0; i < sizeof(array); i++ ) { /* loop through the phrase */
			if (array[i] ==  *argv[1]) /* if the current letter matches the arg */
				array[i] = '\n'; /* swap the mf */

			}

		puts(array); /* writes the string s and a trailing newline to stdout (man pages) */

	} else {
		printf("Give me smth to work with\n");
		return 1;
	}

    fclose(stdin);

	
	return 0;	
}
