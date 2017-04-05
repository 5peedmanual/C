#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZEMATTERS 100 /* preprocessor <name> <size> */

int main(int argc, char *argv[]) { //argv and argc sao os command line arguments that are passed to main() (a partir da consola)
	/* local variables */
	int i, length; /* integer variables */
	char array[SIZEMATTERS]; /* character array */

	fgets (array, SIZEMATTERS, stdin); /* fgets(endereço_da_variável, num_max_caracteres, standard_input) */
	
	do { //do whats in here 
		length = strlen (array); /* length of the string in the array */
		for ( i = 0; i < length; i++ ) { /* loop through the string */
			if (v[i] ==  argv[1][0]) { /* if the current letter matches the argument */
				v[i] = '\n'; /* swap */
				printf("%s", array); /* print the rest */
			}
		}
	} while (fgets(array, SIZEMATTERS, stdin)!=NULL); //while the fgets is not null

    	return 0;
}
