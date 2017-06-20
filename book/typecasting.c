#include <stdio.h>

int main() {

	int a, b;
	float c, d;

	a = 13;
	b = 5;

	//Divide using integers
	c = a / b;
	//Divide using floats
	d = (float) a / (float) b;

	printf("[intergers]\t a = %d\t b = %d\n", a, b);
	printf("[floats]\t c = %f\t d = %f\n", c, d);

	return 0;

}
