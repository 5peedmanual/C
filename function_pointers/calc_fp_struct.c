#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct calculator {
	int (*add)(int a, int b);
};

int add(int a, int b)
{
	return a + b;
}

struct calculator *initialize(void)
{
	struct calculator *init_calc = malloc(sizeof(struct calculator));
	init_calc->add = add;
	return init_calc;
}

void main(int argc, char **argv)
{
	struct calculator *p = initialize();
	int a = 2;
	int b = 3;
	int res;

	//res = p->add(a,b);
	printf("%d\n", p->add(a,b));
}



	
