#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void divide(int A[], int n)
{
	int i, k;
	static int b = 0;
	k = 0;
 	for (i = 7; i >= 0; i--) {
		k = n >> i;
		if (k & 1) {
			printf("1");
			set_bit(A,b);
		} else {
			printf("0");
		}
		b++;
	}
	printf("\n");
}
