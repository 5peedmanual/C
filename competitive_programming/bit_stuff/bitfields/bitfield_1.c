#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
	unsigned int ready	:1;
	unsigned int enable	:1;
	unsigned int receivedb	:1;
} receiver;

void main(void)
{
	int data;
	data = receiver.receivedb;
	receiver.ready = 0;
	receiver.enable = 1;
}

