#include <stdio.h>

void function3() {
	int i = 11;
	printf("\t\t\t[in function3] i = %d\n", i);
}

void function2() {
	int i = 7;
	printf("\t\t[in function2] i = %d\n", i);
	//Call function3
	function3();
	printf("\t\t[back in function2] i = %d\n", i);
}

void function1() {
	int i = 1;
	printf("\t[in function1] i = %d\n", i);
	//Call function2
	function2();
	printf("\t[back in function1] i = %d\n", i);
}

int main() {
	int i = 3;
	printf("[in main] i = %d\n", i);
	//Call function1, which calls function2, that calls 3();
	function1();
	printf("[back in main] i = %d\n", i);


	return 0;
}
