#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void main(void)
{
	const char char1 = 'b';
	const char char2 = 'a';


	printf("char1:  %c %d char2: %c %d \n", char1, char1, char2, char2);
	int ret = strcmp(&char1, &char2);
	 printf("%d\n", ret);
	
 	if (char1 > char2)
 		puts("char1 > char2");
 	else
 		puts("char2 > char1");


}
