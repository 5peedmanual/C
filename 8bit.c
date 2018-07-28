#include <stdio.h>
#include <stdlib.h>

struct eight_bit {
	char ch;
	unsigned short ascii;
};


enum b_t {
	one_p		= 0x01,
	two_p		= 0x02,
	four_p		= 0x04,
	eight_p		= 0x08,
	sixteen_p	= 0x10,
	thirtytwo_p	= 0x20,
	sixtyfo_p	= 0x40,
	onetwoei_p	= 0x80,
} bits;

	

void divide(unsigned short n)
{
	unsigned short remainder, result;
	int num;
	while(n != 0) {
		printf("%d", n);
		remainder = n % 2;
		n = n / 2;
		printf("n / 2: %d remainder: %d \n",
			       n, remainder);
	}
}
void main(void)
{
	struct eight_bit pt;
	char a = 'A';
	unsigned short a_ascii = a;
	unsigned short num;
	printf("%d \n", a_ascii);	
	divide(a_ascii);
}

