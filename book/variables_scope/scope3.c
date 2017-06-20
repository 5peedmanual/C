#include <stdio.h>

int j = 42; //global variable

void function3() {
	int i = 11, j = 999; //j is a variable of function3()
	printf("\t\t\t[in function3] i @ 0x%p = %d\n", &i, i);
	printf("\t\t\t[in function3] j @ 0x%p = %d\n", &j, j);
}

void function2() {
	int i = 7;
	printf("\t\t[in function2] i @ 0x%p = %d\n", &i, i);
	printf("\t\t[in function2] j @ 0x%p = %d\n", &j, j);	
	printf("\t\t[in function2] setting j = 1337\n");
	j = 1337;
	function3();
	printf("\t\t[in function2] i @ 0x%p = %d\n", &i, i);
	printf("\t\t[in function2] j @ 0x%p = %d\n", &j, j);	

}

void function1() {
	int i = 5;
	printf("\t\t[in function1] i @ 0x%p = %d\n", &i, i);	
	printf("\t\t[in function1] j @ 0x%p = %d\n", &j, j);	
	function2();
	printf("\t\t[in function1] i @ 0x%p = %d\n", &i, i);	
	printf("\t\t[in function1] j @ 0x%p = %d\n", &j, j);
}

int main() {
	int i = 3;	
	printf("\t\t[in main] i @ 0x%p = %d\n", &i, i);	
	printf("\t\t[in main] j @ 0x%p = %d\n", &j, j);	
	function1();
	printf("\t\t[back in main] i @ 0x%p = %d\n", &i, i);	
	printf("\t\t[back in main] j @ 0x%p = %d\n", &j, j);	
	return 0;
}
