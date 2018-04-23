#include <stdio.h>
#include <stdlib.h>


#define ARSIZE 10

struct wp_char {
	char wp_cval;
	short wp_font;
	short wp_psize;
} ar[ARSIZE];

void infun(struct wp_char *);

int main(void)
{
	struct wp_char wp_tmp, *lo_index, *hi_index, *in_p;

	for (in_p = ar; in_p < &ar[ARSIZE]; in_p++) {
	       infun(in_p);
       		if (in_p->wp_cval == '\n')
	 		break;
	}

	if (in_p - ar > 1)
		for (lo_index = ar; lo_index <= in_p-2; lo_index++) {
			for (hi_index = lo_index+1; hi_index <= in_p-1; hi_index++) {
				if (lo_index->wp_cval > hi_index->wp_cval) {
					struct wp_char wp_tmp = *lo_index;
					*lo_index = *hi_index;
					*hi_index = wp_tmp;
				}
			}
		}

	for (lo_index = ar; lo_index < in_p; lo_index++) {
		printf("%c %d %d\n", lo_index->wp_cval,
				lo_index->wp_font, lo_index->wp_psize);
	}
	
	exit(0);
}

void infun(struct wp_char *inp)
{
	inp->wp_cval = getchar();
	inp->wp_font = 2;
	inp->wp_psize = 10;
	return;
}
