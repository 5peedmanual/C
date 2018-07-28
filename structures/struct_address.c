#include <stdio.h>

struct foo {
	int a;
}

main(void)
{
	struct foo f;
	printf("address of f = %x\n", &f);
	printf("address of f.a = %x\n", &f.a);
}
