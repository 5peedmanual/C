#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strcpy
#include <ctype.h>


/*
   0x080483da <+15>:	mov    DWORD PTR [eax],0x30303130
   0x080483e0 <+21>:	mov    DWORD PTR [eax+0x4],0x31303030
   0x080483e7 <+28>:	mov    DWORD PTR [eax+0x8],0x30313030
   0x080483ee <+35>:	mov    DWORD PTR [eax+0xc],0x30303131
   0x080483f5 <+42>:	mov    DWORD PTR [eax+0x10],0x30303030
   0x080483fc <+49>:	mov    DWORD PTR [eax+0x14],0x30303030
   0x08048403 <+56>:	mov    DWORD PTR [eax+0x18],0x30303030
   0x0804840a <+63>:	mov    DWORD PTR [eax+0x1c],0x30303030
   0x08048411 <+70>:	mov    BYTE PTR [eax+0x20],0x0
*/


void escreve_IEEE_strings(char sinal, char* expoente, char* mantissa) {
	printf ("sinal: %c\n", sinal);
	printf ("expoente: %s\n", expoente);
	printf ("mantissa: %s\n", mantissa);
}


int main() {
	
	int i;
	char binary[32], sinal, expoente[8], mantissa[23];
	char *pointer_to_binary, *sinal_pointer, *expoente_start_pointer, *expoente_pointer, *mantissa_start_pointer;
	float valor;
	pointer_to_binary = binary;

	printf("Enter binary: \n");
	fgets(binary, 32, stdin);
	//strcpy(binary, "01000001001011000000000000000000");


	printf("address of binary: %p\n", &binary);
	printf("address of pointer to binary: %p\n", &pointer_to_binary);
	//pointer_to_binary its pointing to the beginning of binary so its value is 0
	printf("value of pointer_to_binary: %c\n", *pointer_to_binary);
	//sinal
	sinal_pointer = pointer_to_binary;
	printf("sinal_pointer address %p\n", sinal_pointer);
	printf("sinal_pointer value: %c\n", *sinal_pointer);
	sinal = *sinal_pointer;
	//EXPOENT
	expoente_start_pointer = pointer_to_binary + 1; //start
	printf("expoente_start address: %p\n", expoente_start_pointer);
	printf("expoente_start value: %c\n", *expoente_start_pointer);
	
	//expoente_pointer = ((char *) expoente_start) + (10 * sizeof(char));	
	
	//printf("expoente_pointer address: %p\n", expoente_pointer);
	//printf("expoente_pointer value: %c\n", *expoente_pointer);

	for ( i = 0; i < 9; i++) { 
		printf("value :%c\n", *expoente_start_pointer);
		printf("ADDRESS: %p\n", expoente_start_pointer);
		//found the problem
		if ( i == 8 ) {
			expoente[i] = '\0'; //Add the null pointer to the end
			break;
		}
		expoente[i] = *expoente_start_pointer;
		expoente_start_pointer += 1;	
	}
		
	//JA SEI 
	/* 4:30 */
	//got it :,)

	printf("expoente value: %s\n", expoente);
	printf("expoente address: %p\n", &expoente);
	
	//mantissa

	mantissa_start_pointer = pointer_to_binary + 9;
	printf("mantissa_pointer address %p\n", mantissa_start_pointer);
	printf("mantissa_pointer value: %c\n", *mantissa_start_pointer);

	for ( i = 0; i < 22; i++ ) {
		if ( i == 21 ) {
			mantissa[i] = '\0'; //Add the null pointer to the end
			break;
		}
		mantissa[i] = *mantissa_start_pointer;
		mantissa_start_pointer += 1;
	}
				
	printf("mantissa value: %s\n", mantissa);
	printf("mantissa address: %p\n", &mantissa);
	printf("\n");	
	printf("\n");	
	//tudo fixe call the function to print 
	escreve_IEEE_strings(sinal, expoente, mantissa);


	return 0;
}
