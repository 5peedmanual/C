#include <stdio.h>


#define  NUMBITS (8*sizeof(int))

void printBin( float x ) {
   unsigned int num = *(unsigned int*)&x;
   int i;

   for ( i=0; i<NUMBITS; i++ ) {
     printf("%d", num>>(NUMBITS-1) );
     num = num<<1;
   }
   printf("\n");
}

void escreve_IEEE(char sinal, int expoente, float mantissa) {
   printf ("sinal: %c\n", sinal);
   printf ("expoente: %d\n", expoente);
   printf ("mantissa: %.8f\n", mantissa);
}


int getExpo( float x ) {
   union { float f; unsigned int i; } num;

   num.f = x;
   num.i = (num.i>>23) & 0xff;  // obter os 8bits que codificam o exp
   return num.i-127;
}

float getMant( float x ){
   union { float f; unsigned int i; }  num;
 
   num.f = x;
   num.i = (num.i & 0x007fffff) | 0x3f800000; // por bit sinal a 0
                                             // e 127 no exp (i.e. exp=0)
   return num.f;
}



int main( int argc, char *argv[] ) {
   float f;

   if ( scanf("%f", &f ) != 1 ) {
      printf("Erro no numero\n");
      return 1;
   }

   printf("bits: ");
   printBin( f );

   char sinal='+';
   if ( f < 0.0 ) sinal='-';

   int expo = getExpo( f );
   float mant = getMant( f );

   escreve_IEEE( sinal, expo, mant );

   return 0;
}

