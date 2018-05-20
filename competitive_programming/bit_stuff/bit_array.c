#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	unsigned int flag = 1;
	i = k / 32;
	pos = k % 32;
	flag = flag << pos;
	if (A[i] & flag) { // test the bit at the k-th position in A[i]
		// k-th bit is 1
		printf("1 ");
		return 1;
	} else {
		// is 0
		printf("0 ");
		return 0;
	}

}

void divide(int A[], unsigned short n)
{
	unsigned short remainder, result;
	int num;
	int b = 0;
	while (n != 0) {
		remainder = n % 2;
		if (remainder == 1 )
			set_bit(A, b);
		n /= 2;
		b++;
	}

}


void main(void)
{
	int A[8];
	int bit_arr[8];
	unsigned short ret;
	int j, r;
	char a = 'a';
	unsigned short a_ascii = a;
	printf("%d \n", a_ascii);
	memset(A, 0, 1); // clear the bit array
	divide(A, a_ascii);
	for (j = 0, r = 7; j < 7, r >= 0; j++, r--) {
		ret = test_bit(A, j);
		printf("j = %d r = %d ret = %d \n",j,r, ret);
		bit_arr[r] = ret;
	}
	printf("\n");
	for (j = 0; j < 8; j++)
		printf("%d ", bit_arr[j]);
	printf("\n");

}
