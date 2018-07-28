#include <stdio.h>

#define TEXTO_HTML(text) printf("<h1>%s</h1>\n", #text);

void main(void) 
{
	TEXTO_HTML(asd)
}
