#include <stdio.h>
#include <stdlib.h>

struct node {
	int x;
	struct node *next;
}

int main(void)
{
	// unchanged first node
	struct node *root;

	// point root to node struct
	root = (struct node *) malloc(sizeof(struct node));

	// the node root points to has its next pointer 
	// equal to a null pointer set
	root->next = 0;

	// modify what node pointer root points to
	root->x = 5;

}

