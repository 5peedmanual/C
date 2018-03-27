#include <stdio.h>
#include <stdlib.h>

struct foo {
	int a;
	int b;
};

void change_foo(struct foo *f)
{
	f->a = 4;
	f->b = 5;
}

int main(void)
{
	struct foo f = {1,2};
        printf("beginning foo: %d %d\n", f.a, f.b);
	change_foo(&f);
	printf("final foo: %d %d\n", f.a, f.b);
	exit(0);
}
