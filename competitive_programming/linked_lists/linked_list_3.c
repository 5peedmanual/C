#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
} array[3];

void print_node(struct node *pointer);

int main(void)
{
	struct node *lp;

	array[0].data = 5;
	array[0].next = &array[1];
	array[1].data = 6;
	array[1].next = &array[2];
	array[2].data = 7;
	array[2].next = NULL; // end of list

	print_node(lp);
	exit(0);
}

void print_node(struct node *pointer)
{
	pointer = array; // point to root
	while (pointer) {
		printf("content %d\n", pointer->data);
		pointer = pointer->next; // point to next node
	}
}
