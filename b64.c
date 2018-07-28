#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct 8bit {
// 	 

struct b64 {
	char ch;
	unsigned short ascii;
// 	struct 8bit *8b_p;
// 	struct 6bit *6b_p;
	unsigned short ascii_6b;
//	struct b64 *next;
};


void get_ascii(char ctoascii);

void main(void)
{
	const char string[] = "Hello World";
	int i;
	unsigned 
	for (i = 0; i < 11; i++) {
		printf("%c ", string[i]);
		get_ascii(string[i]);		

	}
}

void get_ascii(char ctoascii)	
{
	unsigned short ascii;
	ascii = ctoascii;
	printf("%d\n", ascii);
}	
		
