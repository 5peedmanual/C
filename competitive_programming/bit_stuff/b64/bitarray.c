#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void set_bit(int A[], int k)
{
	int i, pos;
	unsigned int flag = 1;
	i = k / 32; // gives the index in the array
	pos = k % 32; // gits the bit position in A[i]
	flag = flag << pos; // shift k positions	
	A[i] = A[i] | flag;
}


unsigned short test_bit(int A[], int k)
{
	int i, pos;
	struct foo *p;
	unsigned int flag = 1;
	i = k / 32;
	pos = k % 32;
	flag = flag << pos;
	if (A[i] & flag) { // test the bit at the k-th position in A[i]
		// k-th bit is 1
		// printf("1 ");
		return 1;
	} else {
		// is 0
		// printf("0 ");
		return 0;
	}
}
