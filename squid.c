#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void escreve_IEEE_valores(char sinal, int expoente, float mantissa,
float valor) {
	printf("%c %.10f * 2^%d\n", sinal, mantissa, expoente);
	printf("valor: %.10f\n", valor);
}
//binary para o expoente
int convertBinaryToDecimal(long long n) {
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0) {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}
//expoente string to int
int function_expoente(char *expoente) {
	int e = atoi(expoente);
	int final_expoente = convertBinaryToDecimal(e);
	return final_expoente -127;
	
}

//mantissa
float function_mantissa(char *mantissa) {
	int i;
	float num1 = 1;
  	for (i = 0; i < strlen (mantissa); i++) {
      		if (mantissa[i] == '1')
		num1 += (float) 1 *(pow (2, -(i + 1)));
    	}
  	return num1;
}


float final(char sinal, float e, float m) {
	float num2;
	if ( sinal == '1') {
		num2 = -1 * (m) * pow(2,e);
	} else {
		num2 = 1 * (m) * pow(2,e);
	}
	return num2;
}

int main(int argc, char *argv[]) {	
	int i;
	char binary[33], sinal, sinal_print, expoente[8], mantissa[23];
	char *pointer_to_binary, *sinal_pointer, *expoente_start_pointer, *expoente_pointer, *mantissa_start_pointer;
	float valor;
	long long n;
	pointer_to_binary = binary;

	fgets(binary, 33, stdin);
	sinal_pointer = pointer_to_binary;
	//sinal for the functions
	sinal = binary[0];
	//sinal for the print
	if ( binary[0] == '1' ) {
		sinal_print = '-';
	} else {
		sinal_print = '+';
	}

	expoente_start_pointer = pointer_to_binary + 1; //start

	for ( i = 0; i < 9; i++) { 
		if ( i == 8 ) {
			expoente[i] = '\0'; //Add the null pointer to the end
			break;
		}
		expoente[i] = *expoente_start_pointer;
		expoente_start_pointer += 1;	
	}
	mantissa_start_pointer = pointer_to_binary + 9;
	for ( i = 0; i < 24; i++ ) {
		if ( i == 23) {
			mantissa[i] = '\0'; //Add the null pointer to the end
			break;
		}
		mantissa[i] = *mantissa_start_pointer;
		mantissa_start_pointer += 1;
	}
	int final_expoente = function_expoente(expoente);
	float final_mantissa = function_mantissa(mantissa);
	valor = final(sinal, final_expoente, final_mantissa);
	escreve_IEEE_valores(sinal_print, final_expoente, final_mantissa, valor);
	return 0;
}


