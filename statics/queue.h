#ifndef QUEUE__H
#define QUEUE__H

#include <stdbool.h>

typedef void * pointer;
typedef struct _Queue Queue;

Queue * queue_new (int size);
void queue_destroy (Queue * self);
void queue_reset (Queue * self);

void queue_push (Queue * self, pointer value);
pointer queue_pop (Queue * self);
pointer queue_get_data_at_front (const Queue * self);

bool queue_is_empty (const Queue * self);
bool queue_is_full (const Queue * self);

#endif
