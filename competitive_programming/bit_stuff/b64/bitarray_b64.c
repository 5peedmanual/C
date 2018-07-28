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


void split(int *array, unsigned number_of_bits, unsigned size);



void main(void)
{
	unsigned short ret;
	int j, r;
	const char string[] = "M";
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



void split(int *array, unsigned number_of_bits, unsigned size)
{
	int six_;
	int i,j;
	static unsigned short count = 0;
	unsigned short decimal;
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
		printf("i: %d count: %d size: %d decimal: %d \n", i,
				count, size, decimal );
	//	encode(decimal,
		size -= 1;
	}
}	 



