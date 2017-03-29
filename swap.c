#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	int i;
	//argument
	char c;
	//array for string
	char array[50];
	
	if (argc < 1)
		printf("no args given");
		exit(1);
	c = (char *) argv[0];
	
	printf("%c\n",c);
			 
		
	printf("Enter a phrase: \n");
	scanf("%s", &array);
	//#fgets(*array, 50, stdin)
	

	for ( i = 0; i < sizeof(array); i ++) {
		if (array[i] ==  c)
			array[i] = '\n';
			
	}





	printf(array);
	
	return 0;	
}

