#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const b64_chars[] =		{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

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

void divide(int A[], int n)
{
	int i, k;
	static int b = 0;
// 	while (n != 0) {
// 
// 		printf("%d ", n);
// 		remainder = n % 2;
// 		if (remainder == 1 )
// 			set_bit(A, b);
// 		n /= 2;
// 		b++;
// 		printf("%d ", remainder);
// 	}
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

void split(int *array, unsigned number_of_bits, unsigned size)
{
	int six_;
	int i,j;
	static unsigned short count = 0;
	unsigned short decimal;
	printf("number_of_bits %d \n", number_of_bits);
	int ninefo = number_of_bits-6;
	while (size+1) { // loop for each letter
		decimal = 0;
		for (i = count, j = count+6; i < j; i++) {
			if (j > number_of_bits)
				return;
			// printf("%d ", array[i]);
			printf("i: %d j: %d \n", i, j);
			decimal = decimal << 1 | array[i];
		}
		count += 6;
		j += 6;
		printf("\n");
		printf("i: %d count: %d size: %d decimal: %d char: %c\n", i,
				count, size, decimal, decimal);
		size -= 1;
	}

}	 


void main(void)
{
	unsigned short ret;
	int j, r;
	const char string[] = "Man";
	unsigned short string_size = sizeof(string)-1;
	unsigned short numof_bits = string_size * 8;
	int A[10], array_bit[numof_bits], six_bit_arr[numof_bits], ascii_arr[10];


	memset(A, 0, 10); // clear the bit array
	memset(array_bit, 0, numof_bits);
	
	for (j = 0; j < string_size; j++) {
		ascii_arr[j] = string[j]; // get ascii
		printf("%d \n", ascii_arr[j]);
		divide(A, ascii_arr[j]); // decimal ascii to binary
	}

	for (j = 0; j < numof_bits; j++) {
		ret = test_bit(A, j);
		array_bit[j] = ret;
	}

	printf("\n\n\n8 bit array: \n");
	for (j = 0; j < numof_bits; j++)
		 printf("%d", array_bit[j]);
	printf("\n\n\n");
	split(array_bit, numof_bits, string_size); 
}
