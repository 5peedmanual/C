#include <stdio.h>
#include <stdlib.h>


int i_to_binary(int num);

int main(void)
{
	int i, i_bin;
	for (i = 0; i <= 10; i++) {
		printf("(%d&1) == %d\n", i, (i&1));
		printf((i&1) ? "odd\n" : "even\n");
	}

	exit(EXIT_SUCCESS);
}

int i_to_binary(int num) 
{
	int remainder, binary, i;
	i = 1;
	binary = 0;
	do {
		remainder = num % 2;
		num = num / 2;
		binary = binary + (remainder * i);
		//	printf("binary: %d ", binary);
		i = i * 10;
		//	printf("i*10: %d\n", i);
	} while (num != 0);
	return binary;
}

