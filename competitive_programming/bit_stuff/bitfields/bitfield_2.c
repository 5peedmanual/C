#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct __attribute__((__packed__)) mystruct_A {
    unsigned int a	:1;
    unsigned int b	:1;
} s0 = { 0 ,1 };


struct foo {
	int a;
	unsigned int b;
	unsigned int c;
} s1 = { 1, 2, 3 };

struct bar {
	unsigned int a	:1;
	unsigned int b	:1;
} s2 = { 1, 0 };


void main(void)
{
	// s2.c = 4;
	printf("size of s0 is %u\n", sizeof(struct mystruct_A));
	printf("sizeof foo is %u\n", sizeof(struct foo));
	printf("size of bar is %u\n", sizeof(struct bar));
	printf("s2.a %d\n", s2.a);
	printf("s2.b %d\n", s2.b);

}

