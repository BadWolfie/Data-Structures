#ifndef STACK__H
#define STACK__H

#include <stdbool.h>

typedef void * pointer;
typedef struct _Stack Stack;

Stack * stack_new (int size);
void stack_destroy (Stack * self);
void stack_reset (Stack * self);

void stack_push (Stack * self, pointer value);
pointer stack_pop (Stack * self);
pointer stack_get_data_at_top (const Stack * self);

bool stack_is_empty (const Stack * self);
bool stack_is_full (const Stack * self);

#endif
