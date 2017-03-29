#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
ja te mando
o powerpoint
tipo
1 numero em binario
no IDEE 754
e nesses 32 bits
o 1º bit esta reservado para o sinal
os outros 11 para o expoente
e os outros
para a mantiassa
*/

#define  NUMBITS (8*sizeof(int))
#define SINAL_SIZE 1
#define EXPOENT_SIZE 8
#define MANTISSA 23
//0
//10000010
//01011000000000000000000
void escreve_IEEE_strings(char sinal, char*	expoente, char*	mantissa) {
	printf ("sinal: %s\n", sinal);
	printf ("expoente: %s\n", expoente);
	printf ("mantissa: %s\n", mantissa);
}


int main(int argc, char *argv[]) {
	int s, m ,e;
	char sinal[10], expoente[30], mantissa[30];
	char binary[32];
	float valor;

	strcpy(binary, "01000001001011000000000000000000");
	for (s = 0; s < 1; s++){
		sinal[s] = binary[s];
		//printf("%c\n", sinal[s]);
	}

	for (e = 1; e < 9; e++) {
		expoente[e] = binary[e];
		//printf("%c", expoente[m]);
	}

	for (m = 9; m < 32; ++m) {
		mantissa[m] = binary[m];
		//printf("%c", mantissa[i]);
	}

	escreve_IEEE_strings(sinal, expoente, mantissa);
	printf("\n");
	return 0;
}