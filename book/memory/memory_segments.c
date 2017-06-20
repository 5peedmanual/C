#include <stdio.h>

int global var;
int global_initialized_var = 5;


void function() {
	int stack_var;
	printf("the function's stack_var is at address %p\n", &stack_var);
}

int main() {
	int stack_var;
	static int static_initialized_var = 5;
	static int static_var;
	int *heap_var_ptr;

	heap_var_ptr = (int *) malloc(4);
	
	//these variables are in the data segment
	printf("global_initialized_var is at address %p\n", &global_initialized_var);
	printf("static_initialized_var is at address %p\n", &static_initialized_var);

	//these variables are in the bss segment
	printf("static_var is at address %p\n", &static_var);
	printf("global_var is at address %p\n", &global_var);

	
	
	
