#include <stdio.h>
#include <stdlib.h>

struct foo {
	int a;
	int b;
};
void print_change_foo(struct foo f)
{
	printf("beginning foo: %d %d\n", f.a, f.b);
	f.a = 4;
	f.b = 5;
        printf("changed foo: %d %d\n", f.a, f.b);
}

int main(void)
{
	struct foo f;
	f.a = 1;
	f.b = 2;
	print_change_foo(f);
	printf("final foo: %d %d\n", f.a, f.b);
	exit(0);
}


