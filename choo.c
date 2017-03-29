#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



/*
int getsin(char *array_arg) {
	int sinal;
	char *pointer_array;
	pointer_array = array_arg;
	sinal = pointer_array - 31; 
	return sinal;
}
}
*/

void escreve_IEEE_strings(char* sinal, char *expoente, char* mantissa, float valor) {
	printf("sinal: %c\n", *sinal);
	printf("expoente: %s\n", expoente);
	printf("mantissa: %s\n", mantissa);
	printf("valor: %f\n", valor);
}	

int main() {

	/* em vez de fazer chop chop na string, i just point to to parts of the string */
	


	int i;
	char array[32], expoente[10];
	//assign pointer array to array
	char *pointer_to_binary, *sinal, *mantissa;
	char *expoente_start, *expoente_end;
	pointer_to_binary = array;
	float valor;
	if ( scanf("%s", &array) != 1) {
		printf("Error!\n");
		return 1;
	}

	for ( i = 0; i < 32; i++ ) {
		printf("%c", *pointer_to_binary);
		pointer_to_binary =  (char *) pointer_to_binary + 1;
	}

	printf("\n");
	sinal = pointer_to_binary - 31;
	expoente_start = pointer_to_binary - 30;
	for ( i = 0; i < 10; i++) {
		printf("%c", expoente[i]);
		expoente[i] = pointer_to_binary[i];
	}	
	printf("\n"); 
	mantissa = pointer_to_binary -22;
	valor = 10;

	//For print
	//escreve_IEEE_strings(sinal, expoente, mantissa, valor);	

	return 0;
}	 
