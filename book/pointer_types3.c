#include <stdio.h>

int main() {

	int i;
	
	//Defining the arrays
	char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
	int int_array[5] = {1, 2, 3, 4, 5};

	//Defining the pointer
	char *char_pointer;
	int *int_pointer;

	//Defining the pointers to the arrays
	char_pointer = (char *) int_array; //Typecast into the 
	int_pointer = (int *) char_array; //pointer's data type
	

	//Iterate through the int array with the int_pointer
	for( i = 0; i < 5; i++ ) {

	printf("[interger pointer] points to %p, which contains the integer %c\n", 		int_pointer, *int_pointer);
	int_pointer = (int *) ((char *) int_pointer + 1);
	
	}

	//Iterate through the char array with the char_pointer
	for ( i = 0; i < 5; i++ ) {

	
	printf("[char pointer] points to %p, which contains the char %d\n", 			char_pointer, *char_pointer);
	char_pointer = (char *) ((int *) char_pointer + 1);

	}

	return 0;

}

