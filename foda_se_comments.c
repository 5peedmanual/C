#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void escreve_IEEE_strings(char sinal, char* expoente, char* mantissa, float valor) {
	printf("   sinal: %c\n", sinal);
	printf("expoente: %s\n", expoente);
	printf("mantissa: %s\n", mantissa);
	printf("   valor: %.10f\n", valor);
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
      		if (mantissa[i] == '1') {
				num1 += (float) 1 *(pow (2, -(i + 1)));
    		}
    }
  	return num1;
}

//final
float function_final(char sinal, float final_expoente, float final_mantissa) {
	float num2;
	if ( sinal == '1') {
		num2 = -1 * (final_mantissa) * pow(2,final_expoente);
	} else {
		num2 = 1 * (final_mantissa) * pow(2,final_expoente);
	}
	return num2;
}

int main() {
	
	/* eu em vez de fazer chop chop a string, usei um pointer (pointer_to_binary) para apontar as diferentes partes da string */
	/* depois faço increment e vou metendo td no array */
	/* local variables */
	int i;
	char binary[33], sinal, expoente[8], mantissa[23]; /* arrays para o input (binary[33]), sinal, expoente e matissa */
	char *pointer_to_binary, *sinal_pointer, *expoente_start_pointer, *expoente_pointer, *mantissa_start_pointer; /* pointers */
	float valor;
	long long n;
	pointer_to_binary = binary;


	//fgets(binary, 33, stdin);
	strcpy(binary, "01000001001011000000000000000000");
	sinal_pointer = pointer_to_binary;
	//sinal for the functions
	sinal = binary[0]; 
	expoente_start_pointer = pointer_to_binary + 1; //start
	printf("\n");	
	printf("\n");	


	printf("address of binary: %p\n", &binary);
	printf("\n");
	printf("address of pointer to binary: %p\n", &pointer_to_binary);
	//pointer_to_binary its pointing to the beginning of binary so its value is 0
	printf("value of pointer_to_binary: %c\n", *pointer_to_binary);
	printf("\n");

	/************************************************************* SINAL *****************************************************************************/
	sinal_pointer = pointer_to_binary;
	printf("sinal_pointer address %p\n", sinal_pointer);
	printf("sinal_pointer value: %c\n", *sinal_pointer);
	sinal = *sinal_pointer;
	printf("\n");


	/************************************************************ EXPOENTE *************************************************************************/
	expoente_start_pointer = pointer_to_binary + 1; // 1bit further
	printf("expoente_start address: %p\n", expoente_start_pointer);
	printf("expoente_start value: %c\n", *expoente_start_pointer);
	

	printf("\n");
	printf("Expoente array: \n");	
	for ( i = 0; i < 9; i++) { 
		
		if ( i == 8 ) {
			expoente[i] = '\0'; //Add the null pointer to the end
			break; /*break the loop */
		}
		printf("value :%c\n", *expoente_start_pointer);
		printf("ADDRESS: %p\n", expoente_start_pointer);
		expoente[i] = *expoente_start_pointer; /* put it in the array */
		expoente_start_pointer += 1;		   /* increment the pointer by 1bit and loop again */

	}

	printf("\n");
	printf("expoente array value: %s\n", expoente);
	printf("expoente array address: %p\n", &expoente);
	printf("\n");
	/************************************************************ MANTISSA *************************************************************************/

	mantissa_start_pointer = pointer_to_binary + 9; // 9bit further
	printf("mantissa_pointer address %p\n", mantissa_start_pointer);
	printf("mantissa_pointer value: %c\n", *mantissa_start_pointer);

	printf("\n");
	printf("Mantissa array: \n");
	for ( i = 0; i < 24; i++ ) {
		if ( i == 23 ) {
			mantissa[i] = '\0'; //Add the null pointer to the end
			break;  /*break the loop */
		}
		printf("value :%c\n", *mantissa_start_pointer);
		printf("ADDRESS: %p\n", mantissa_start_pointer);
		mantissa[i] = *mantissa_start_pointer; /* put it in the array */
		mantissa_start_pointer += 1;		   /* increment the pointer by 1bit and loop again */
	}

	printf("\n");		
	printf("mantissa array value: %s\n", mantissa);
	printf("mantissa array address: %p\n", &mantissa);
	printf("\n");	
	printf("\n");

	//function calls
	int final_expoente = function_expoente(expoente);
	float final_mantissa = function_mantissa(mantissa);
	valor = function_final(sinal, final_expoente, final_mantissa);
	escreve_IEEE_strings(sinal, expoente, mantissa, valor);



	return 0;
}