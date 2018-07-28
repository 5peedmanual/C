#include <stdio.h>
#include <stdlib.h>

struct strt {
	int a;
};

int main(void) 
{
	struct strt *ssp, s_item;
	const struct strt *csstrtp;

	s_item.a = 1;
	ssp = &s_item;
	ssp->a += 2;
	csstrtp = &s_item;
	csstrtp-> = 0; // not permitted csstrtp points to const objects

	exit(0);
}
