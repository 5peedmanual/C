#include <stdio.h>
#include <stdlib.h>

struct node {
	int x;
	struct node *next;
};

int main(void)
{
	struct node *root;
	// this will point to each node it traverses the list
	struct node *walk_through;

	root = malloc(sizeof(struct node));

	root->next = 0;
	root->x = 12;
	walk_through = root; // start at root

	if (walk_through != 0) {
		while (walk_through->next != 0) // will continue as long as there is another pointer in the next
			walk_through = walk_through->next; // goto next node
	}

	// create a node at the end of the list
	walk_through->next = malloc(sizeof(struct node));
	walk_through = walk_through->next;

	if (walk_through == 0) {
		puts("Out of memory");
		exit(0);
	} else {
		// initialize the new memory
		walk_through->next = 0;
		walk_through->x = 42;
	}
	printf("walk_through next: %d\n", walk_through->next);
	printf("walk_through x: %d\n", walk_through->x);

	exit(0);
}

