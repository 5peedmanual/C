#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pstring {
	char * chars;
	int (*len)();
};

int len(struct pstring *self) 
{
	return strlen(self->chars);
}

struct pstring *init_string(int n)
{
	struct pstring *str = malloc(sizeof(struct pstring));

	str->chars = malloc(sizeof(char) * n);
	str->len = len;

	// str[0] = '\0';

	return str;
}

void main(void)
{
	struct pstring *p = init_string(30);
	strcpy(p->chars, "Hello");
	printf("%d\n", p->len(p));
}

