#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

struct _Stack
{
	pointer * data;
	int size;
  int top;
};

Stack *
stack_new (int size)
{
  Stack * self = (Stack *) malloc(sizeof(Stack));
	self->data = (pointer *) malloc(size * sizeof(pointer));
	self->size = size;
	self->top = 0;
  return self;
}

void
stack_destroy (Stack * self)
{
	free(self->data);
	self->top = self->size = 0;
}

void
stack_reset (Stack * self)
{
	free(self->data);
	self = stack_new(self->size);
}


void
stack_push (Stack * self, pointer value)
{
	if (stack_is_full(self)) {
		puts("Stack is full.");
		exit(1);
	}

	self->data[self->top++] = value;
}

pointer
stack_pop (Stack * self)
{
	if (stack_is_empty(self)) {
		puts("Stack is empty.");
		exit(1);
	}

	pointer aux = self->data[self->top--];
	return aux;
}

pointer
stack_get_data_at_top (const Stack * self)
{
	if (stack_is_empty(self)) {
		puts("Stack is empty.");
		exit(1);
	}

	return self->data[self->top - 1];
}


bool
stack_is_empty (const Stack * self)
{
  return (!self->data || self->top == 0);
}

bool
stack_is_full (const Stack * self)
{
  return (self->top == (self->size - 1));
}
                                        
