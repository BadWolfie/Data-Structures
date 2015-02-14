#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

void stack_init(stack * self, int size)
{
	self->list = (datatype *) malloc(size * sizeof(datatype));
	self->size = size;
	self->top = 0;
}

void stack_destroy(stack * self)
{
	free(self->list);
	self->top = self->size = 0;
}

void stack_reset(stack * self)
{
	free(self->list);
	stack_init(self,self->size);
}


void stack_push(stack * self, datatype value)
{
	if (stack_is_full(*self)) {
		puts("Stack is full.");
		exit(1);
	}

	self->list[self->top++] = value;
}

datatype stack_pop(stack * self)
{
	if (stack_is_empty(*self)) {
		puts("Stack is empty.");
		exit(1);
	}

	datatype aux = self->list[self->top--];
	return aux;
}

datatype stack_get_data_at_top(stack self)
{
	if (stack_is_empty(self)) {
		puts("Stack is empty.");
		exit(1);
	}

	return self.list[self.top - 1];
}


bool stack_is_empty(stack self)
{ return (!self.list || self.top == 0); }

bool stack_is_full(stack self)
{ return (self.top == (self.size - 1)); }