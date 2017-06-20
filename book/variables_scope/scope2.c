#include <stdio.h>

int j = 42; //Global variable

void function3() {
	int i = 11, j = 999; //J is now a local variable of function3()
	printf("\t\t\t[in function3] i = %d, j = %d\n", i, j);
}

void function2() {
	int i = 7;
	printf("\t\t[in function2] i = %d, j = %d\n", i, j)/*42*/;
	printf("\t\t[in function2] setting j = 1337\n");
	j = 1337; //Writting to j
	//Call function3()
	function3();
	printf("\t\t[back in function2] i = %d, j = %d\n", i, j/*1337*/);
}

void function1() {
	int i = 5;
	printf("\t[in function1] i = %d, j = %d\n", i, j/*42*/);
	//Call function2()
	function2();
	printf("\t[back in function1] i = %d, j = %d\n", i, j/*1337*/);
}

int main() {
	int i =3;
	printf("[in main] i = %d, j = %d\n", i, j/*42*/);
	//Call function1()
	function1();
	printf("[back in main] i = %d, j = %d\n", i, j);
	
	return 0;
}

