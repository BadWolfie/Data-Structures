#ifndef QUEUE__H
#define QUEUE__H

/* namespace queue_ */

#include <stdbool.h>

typedef char datatype;

typedef struct _queue
{
	datatype * list;
	int size, front, end;
} queue;

void queue_init(queue * self, int size);
void queue_destroy(queue * self);
void queue_reset(queue * self);

void queue_push(queue * self, datatype value);
datatype queue_pop(queue * self);
datatype queue_get_data_at_front(queue self);

bool queue_is_empty(queue self);
bool queue_is_full(queue self);

#endif