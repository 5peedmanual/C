#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void escreve_IEEE_strings(char sinal, char * expoente, char* mantissa, float valor) {
    printf ("   sinal: %c\n", sinal);
    printf ("expoente: %s\n", expoente);
    printf ("mantissa: %s\n", mantissa);
    printf ("   valor: %.10f\n", valor);
}


int expo(char *expoente) {
	  int i;
  int e = -127;
  int k = 7;

  for (i = 0; i < strlen (expoente); i++)
    {
      if (expoente[i] == '1')
	e = e + (1 << k);
      k--;
    }
	return e;
	
}
float man(char *mantissa) {
	int i;
	float f = 1;
  	for (i = 0; i < strlen (mantissa); i++) {
      		if (mantissa[i] == '1')
		f = f + (float) 1 *(pow (2, -(i + 1)));
    	}
  	return f;
}


float final(char sinal, float e, float m) {
	float v = 0;
	if ( sinal == '1') {
		v = -1 * (m) * pow(2,e);
	} else {
		v = 1 * (m) * pow(2,e);
	}
	return v;
}

int main(int argc, char *argv[]) {	
	int i;
	char binary[33], sinal, expoente[8], mantissa[23];
	char *pointer_to_binary, *sinal_pointer, *expoente_start_pointer, *expoente_pointer, *mantissa_start_pointer;
	float valor;
	long long n;
	pointer_to_binary = binary;

	fgets(binary, 33, stdin);
	//scanf("%s", &binary);
	//strcpy(binary, "01000001001011000000000000000000\0");
	sinal_pointer = pointer_to_binary;
	sinal = binary[0];
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


