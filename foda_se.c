#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strcpy
#include <ctype.h>
#include <math.h>

#define total 127;

void escreve_IEEE_strings(char sinal, char *expoente, char *mantissa, float valor) {
	printf ("   sinal: %c\n", sinal);
	printf ("expoente: %s\n", expoente);
	printf ("mantissa: %s\n", mantissa);
	printf ("   valor: %.10f\n", valor);
}


//float getFloat(char sinal, char* expoente)

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

int expo(char *expoente) {
	int e = atoi(expoente);
	int e_int = convertBinaryToDecimal(e);
	//printf("%d\n", e_int);
	return e_int -127;
	
}
float man(char *mantissa) {
	  int i;
  float f = 1;
  for (i = 0; i < strlen (mantissa); i++)
    {
      if (mantissa[i] == '1')
	f = f + (float) 1 *(pow (2, -(i + 1)));
    }
  return f;
}


float final(char sinal, float e, float m) {
	float v;
	if ( sinal == '1') {
		v = -1 * (m) * pow(2,e);
	} else {
		v = 1 * (m) * pow(2,e);
	}
	return v;
}

int main() {
	
	int i;
	char binary[32], sinal, expoente[8], mantissa[23];
	char *pointer_to_binary, *sinal_pointer, *expoente_start_pointer, *expoente_pointer, *mantissa_start_pointer;
	float valor;
	long long n;
	pointer_to_binary = binary;

	//printf("Enter binary: \n");
	//fgets(binary, 32, stdin);
	scanf("%s", &binary);
	//strcpy(binary, "01000001001011000000000000000000\0");
	//sinal
	sinal_pointer = pointer_to_binary;
	sinal = binary[0];
	//EXPOENT
	expoente_start_pointer = pointer_to_binary + 1; //start
	//expoente_pointer = ((char *) expoente_start) + (10 * sizeof(char));		

	for ( i = 0; i < 9; i++) { 
		if ( i == 8 ) {
			expoente[i] = '\0'; //Add the null pointer to the end
			break;
		}
		expoente[i] = *expoente_start_pointer;
		expoente_start_pointer += 1;	
	}
	
	//mantissa
	mantissa_start_pointer = pointer_to_binary + 9;

	for ( i = 0; i < 23; i++ ) {
		if ( i == 22) {
			mantissa[i] = '\0';
			break;
		}
		mantissa[i] = *mantissa_start_pointer;
		mantissa_start_pointer += 1;
	}
				
	

	int e = expo(expoente);
	float m = man(mantissa);
	valor = final(sinal, e, m);
	escreve_IEEE_strings(sinal, expoente, mantissa, valor);
	return 0;
}


