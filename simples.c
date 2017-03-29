#include <stdio.h>
#include <stdlib.h>

// Este programa parece funcionar bem, mas na
// realidade tem dois erros, localize-os e corrija-os...
char *dupstr (char *str) {
	// find the size of the original string
	int size = 0;
	while (str[size] != '\0')
		size++;

	// allocate space for the new string
	char *newstr = malloc (size);

	// copy original string to new string
	int i;
	for (i = 0; i < size; i++)
		newstr[i] = str[i];

	// add the terminator to the string
	newstr[size] = '\0';

	// return the new string
	return newstr;
}

int main (int argc, char *arvg[]) {
	char *s1 = "abcdef";
	char *s2 = (* dupstr) (s1);

	printf ("Original = '%s'\n Copia = '%s'\n", s1, s2);

	return 0;
}

