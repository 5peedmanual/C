#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enumerate.h"

struct wlink saved;

void main(void)
{
	char array[] = {
			"LICENSE\n"
			"compile.sh\n"
			"pclient\n"
			".\n"
			"..\n"
			"Makefile\n"
			"err_handling\n"
			".git\n"
			"\0"
		};
	loop(array, 1024);

}


void loop(char *buffer, unsigned int size)
{
	int letter_pos, w_start, len, arr_count;
	char word[100];
	char c;
	struct wlink *wl;
	arr_count = 0; // counter too loop the array_list
	w_start = 0; // start of the word
	// fill_null_previous(&array_list[arr_count]);

	for (letter_pos = 0; letter_pos < size; letter_pos++) {
		if (buffer[letter_pos] == '\0') {
			fill_null(&array_list[arr_count-1]);
			break;
		}// if null find end of our data

		if (buffer[letter_pos] == '\n') { // if \n found means end of word
			len = letter_pos - w_start; // the Length of our word
			strncpy(word, buffer + w_start, len);
			c = buffer[w_start];
			fill_link(&array_list[arr_count], c, word);
			arr_count += 1; // inc arr_count
			w_start = letter_pos+1; // set the start of the word
					 	//  and skip \n line
		}
		memset(word, 0, 100);
	}
	organize(wl);
}


void fill_null(struct wlink *pointer)
{
	pointer->next = NULL;
}


void fill_link(struct wlink *pointer,  char sc, char *w_buf) // fill the linked list
{
	pointer->start_char = sc; // first character of the word
	strncpy(pointer->word, w_buf, 100); // word
	pointer->next = pointer+1;
}


void organize(struct wlink *st)
{
	unsigned int size = length();
	int i,j, ret;
	char current, next;

	st = array_list;
	current = st->start_char;
	next = st->next->start_char;

	print_link(st);
	for (i = 0; i < size+1; i++) {
		puts("\n\n\n--------------------------------------\n\n");
		for (j = 0; j < size; j++) {
			printf("i: %d j: %d\n", i, j);
			if (st->next == NULL) {
				st = array_list;
				current = st->start_char;
				next = st->next->start_char;
 				break;
			}
			printf("words compared: [ %s, %s ] [ %d %d ]",
				st->word, st->next->word, (char) current, next);

			if (current > next) {
				swap(st);

			printf(" ==> swapped [ %s, %s ] [ %d %d ]\n",
				st->word, st->next->word, current, next);

			} else
				printf(" ==> not swapped \n");
			st = st->next;
			current = st->start_char;
			if (st->next != NULL)
				next = st->next->start_char;
		}
		puts("\n\n\n--------------------------------------\n\n");
		st = array_list;
	}
	print_link(st);

}


unsigned int length(void)
{
	int length = 0;
	struct wlink *current;

	current = array_list;
	while(current) {
		// printf("\nfirst character: %c\n", current->start_char);
		// printf("word: %s\n", current->word);
		length++;
		current = current->next;
	}
	return length;
}


// void swap(char *buff_word, char*buff_word_next, char sc, char next_sc)
void swap(struct wlink *wl)
{
	struct wlink tmp;
	strncpy(tmp.word, wl->word, 100);
 	tmp.start_char = wl->start_char;

	strncpy(wl->word, wl->next->word, 100);
	wl->start_char = wl->next->start_char;

	strncpy(wl->next->word, tmp.word, 100);
	wl->next->start_char = tmp.start_char;

}


void print_link(struct wlink *pointer)
{
	pointer = array_list;
	printf("ARRAY: [ ");
	while (pointer) {
		printf("%s ", pointer->word);
		pointer = pointer->next;

	}
	printf(" ]\n");
}

