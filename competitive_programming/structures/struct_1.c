#include <stdio.h>
#include <stdlib.h>

#define ARSIZE 10

/* array of structures.
 * a function is used to read characters from the programs stdin
 * and return an appropriately initialized structure
 * when a new line has been read or the array is full,
 * the structures are sorted into order depending
 * on the character value, and then printed out
 */

struct wp_char {
	char wp_cval;
	short wp_font; // font can be encoded into a shor (
	short wp_psize; // point size
} ar[ARSIZE];

/* 
 * type of the input function could equally have
 * been declared above;
 * it return a structure and takes no arguments
 */

struct wp_char infun(void);

int main(void)
{
	int icount, lo_index, hi_index;

	// this loop will take the input
	for (icount = 0; icount < ARSIZE; icount++) {
		ar[icount] = infun(); // get char
		/* Lleave the loop. not incrementing
		 * icount means that the '\n' is ignored
		 * in the short */
		if (ar[icount].wp_cval == '\n')
			break;
	}


	/* now a simple exhange sort */
	for (lo_index = 0; lo_index <= icount-2; lo_index++) {
		for (hi_index = lo_index+1; hi_index <= icount-1; hi_index++) {
			printf("lo %c \NNN \n", ar[lo_index].wp_cval);
			printf("hi %c \NNN \n", ar[hi_index].wp_cval);
			if (ar[lo_index].wp_cval > ar[hi_index].wp_cval) {
				// swap the two structures
				struct wp_char wp_tmp = ar[lo_index];
				ar[lo_index] = ar[hi_index];
				ar[hi_index] = wp_tmp;
			}
		}
	}

	// now print
	
	for (lo_index = 0; lo_index < icount; lo_index++) {
		printf(" %c %d %d\n", ar[lo_index].wp_cval, ar[lo_index].wp_font,
				ar[lo_index].wp_psize);
	}

	exit(EXIT_SUCCESS);
}

struct wp_char infun(void) {
	struct wp_char wp_char;

	wp_char.wp_cval = getchar();
	printf("[infun] %c\n", wp_char.wp_cval);
	wp_char.wp_font = 2;
	wp_char.wp_psize = 12;

	return(wp_char);
}
