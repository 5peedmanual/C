#include <stdio.h>
#include <stdlib.h>

#define AR_SIZE 7

struct tree_node {
	int data;
	struct tree_node *left_p, *right_p;
} tree[AR_SIZE];

struct tree_node *tree_search(struct tree_node *ptr_to_root, int v)
{
	while (ptr_to_root) {
		if (ptr_to_root->data == v)
			return (ptr_to_root);
		if (ptr_to_root->data > v)
			ptr_to_root = ptr_to_root->left_p;
		else
			ptr_to_root = ptr_to_root->right_p;
	}

	return (NULL); // value not found no tree left
}

void main(void)
{
	struct tree_node *tree_ptr, *root;
	int i,j;

	for (i = 0; i < AR_SIZE; i++) {
		j = i + 1;
		tree[i].data = j;
		printf("tree[%d].data == %d\n", i, j);
		if (j == 2 || j == 6) {
			tree[i].left_p = &tree[i-1];
			printf("&tree[%d-1] == %d
			tree[i].right_p = &tree[i+1];
		}
		printf("tree[%d].left_p == %d\n", i, tree[i].left_p);
	}

	// root
	
	root = &tree[3];
	root->left_p = &tree[1];
	root->right_p = &tree[5];

	// try the search
	
	tree_ptr = tree_search(root, 2);
	if (tree_ptr)
		printf("found at position %d\n", tree_ptr-tree);
	else
		puts("value not found\n");

	exit(0);
}
