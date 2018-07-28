#include <stdio.h>
#include <stdlib.h>

struct foo {
	int a;
};

void change_foo(struct foo *f)
{
	printf("[in change_foo] a = %d\n", f->a);
	printf("[in change_foo] changing a...\n");
	f->a = 4;
	printf("[in change_foo] a = %d\n", f->a);
	printf("[in change_foo] returning...\n");
}

int main(void)
{
	// struct foo f = {1};
	struct foo f;
	f.a = 1;
	printf("[in main] a = %d\n", f.a);
	change_foo(&f);
	printf("[in main] after return a = %d\n", f.a);
	exit(0);
}
