#include <stdio.h>
#include <stdlib.h>


struct object {
	int a;
	struct so {
		char b;
		// char *c;
	} char_struct;
} int_struct = {
	1, 'j' /* '\0' */
};

int main(void) {
	printf("%d\n", int_struct.a );
	printf("%c\n", int_struct.char_struct.b );

	// int_struct.char_struct.c = 64;
	// printf("%c\n", int_struct.char_struct.c );


}
