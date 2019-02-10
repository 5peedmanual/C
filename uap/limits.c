#include <stdio.h>
#include <limits.h>


void main(void)
{
	// longs 64 bit 8 bytes
	printf("64 bit long 	max: %ld \n", LONG_MAX);
	printf("64 bit long 	min: %ld \n", LONG_MIN);
	printf("64 bit ulong	max: %lu \n", ULONG_MAX); // l u

	// ints 32 bits 4 bytes
	printf("32 bit int	max: %d  \n", INT_MAX);
	printf("32 bit int	min: %d  \n", INT_MIN);
	printf("32 bit uint	max: %u  \n", UINT_MAX); // u

	// shorts 16 bit 2 bytes
	printf("16 bit short	max: %d  \n", SHRT_MAX);
	printf("16 bit short	min: %d  \n", SHRT_MIN);
	printf("16 bit ushort	min: %hu  \n", USHRT_MAX); // h
}
