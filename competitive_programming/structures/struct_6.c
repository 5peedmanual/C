#include <stdio.h>
#include <stdlib.h>

struct xyz {
	float x;
} var_1;

int main(void)
{
	struct abc {
		struct xyz *p;
	} var_2;

	// struct xyz redeclared
	struct xyz {
		struct abc *p;
	} var_3;
}
