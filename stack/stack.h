#ifndef STACK__H
#define STACK__H

/* namespace stack_ */

#include <stdbool.h>

typedef char datatype;

typedef struct _stack
{
	datatype * list;
	int size, top;
} stack;

void stack_init(stack * self, int max);
void stack_destroy(stack * self);
void stack_reset(stack * self);

void stack_push(stack * self, datatype value);
datatype stack_pop(stack * self);
datatype stack_get_data_at_top(stack self);

bool stack_is_empty(stack self);
bool stack_is_full(stack self);

#endif