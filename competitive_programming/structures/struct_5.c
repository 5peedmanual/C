#include <stdio.h>
#include <stdlib.h>

struct x; /* incomplete type*/
// even with an incomplete type (with out being declared) with can make pointers to structures
struct x *p, func(void); 


void f1(void)
{
	struct x { int i; }; // redeclare
}

// full declaration
struct x {
	float f;
} s_x;

void f2(void)
{
	// valid statements
	p = &s_x;
	*p = func();
	s_x = func();
}

struct x func(void)
{
	struct x tmp;
	tmp.f = 0;
	return (tmp);
}

int main(void)
{
	f1();
	f2();
	func();
}
