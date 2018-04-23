#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct node {
	int data;
	int key;
	struct node *next;
};

//		NODE			NODE
// |HEAD|---> |DATA ITEMS|NEXT| --> |DATA ITEMS|NEXT| --> NULL

struct node *head = NULL;
struct node *current = NULL;

// display the list
void print_list(void)
{
	struct node *root = head;
	printf("\n[ ");

	// start from the beginning
	while (root != NULL) {
		printf("(%d,%d) ", root->key, root->data;
		root = root->next;
	}

	printf(" ]");
}

// inset link at the first location
void insert_first(int key, int data)
{
	// create a link
	struct node *link = (struct node *) malloc(sizeof(struct node));

	link->key = key;
	link->data = data;

	// point it to the old first node
	link->next = head;
}

// delete first item
struct node *delete_first(void) 
{
	// save reference to first link
	struct node *tmp_link = head;

	// mark next to first link as first
	head = head->next;

	// return the deleted link
	return tmp_link;
}

bool is_empty(void)
{
	return head == NULL;
}

int length(void) 
{
	int length = 0;
	struct node *current;
	for (current = head; current != NULL; current = current->next) {
		length++;
	}

	return length;
}

// find a link with given key
struct node *find(int key)
{
	// start from the first link
	struct node *current = head;
	// if list is empty retun null
	if (head == NULL)
		return NULL;
	// navigate through the list
	while (current->key != key) {
		// if its the last node
		if (current->next == NULL)
			return NULL;
		else // goto next link
			current = current->next;
	}
	// if data found, return the current link
	return current;
}

// delete a link with given key
struct node *delete(int key)
{
	// start from the first link
	struct node *current = head;
	struct node *previous = NULL;

	if (head == NULL)
		return NULL;

	// navigate through the list
	while (current->key != key) {
		// if its the last node
		if (current->next == NULL)
			return NULL;
		else {
			// store reference to current link
			previous = current;
			// move to next link
			current = current->next;
		}
	}

	// found a match, update the link
	if (current == head)
		head = head->next; // change first to point to next link
	else
		previous->next = current->next; // bypass the current link

	return current;

}

void sort(void) 
{
	int i, j, k, tmp_key, tmp_data;
	struct node *current;
	struct node *next;

	int size = length();
	k = size;

	for (i = 0; i < size-1; i++, k--) {
		current = head;
		next = head->next;

		for ( j = 1; j < k; j++) {
			if (current->data > next->data) {
				tmp_data = current->data;
				current->data = next->data;
				next->data = tmp_data;

				tmp_key = current->key;
				current->key = next->key;
				next->key = tmp_key;
			}
			current = current->next;
			next = next->next;
		}
	}
}

void reverse












