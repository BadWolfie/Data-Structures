#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

void queue_init(queue * self, int size)
{
	self->list = (datatype *) malloc(size * sizeof(datatype));
	self->front = self-> end = 0;
	self->size = size;
}

void queue_destroy(queue * self)
{
	free(self->list);
	self->front = self-> end = 0;
}

void queue_reset(queue * self)
{
	free(self->list);
	queue_init(self,self->size);
}


void queue_push(queue * self, datatype value)
{
	if (queue_is_full(*self)) {
		puts("Queue is full.");
		exit(1);
	}

	self->end = (self->end + 1) % self->size;
	self->list[self->end] = value;
}

datatype queue_pop(queue * self)
{
	if (queue_is_empty(*self)) {
		puts("Queue is empty.");
		exit(1);
	}

	self->front = (self->front + 1) % self->size;
	return self->list[self->front];
}

datatype queue_get_data_at_front(queue self)
{
	if (queue_is_empty(self)) {
		puts("Queue is empty.");
		exit(1);
	}

	return self.list[self.front];
}


bool queue_is_empty(queue self)
{ return (self.front == self.end); }

bool queue_is_full(queue self)
{ return (self.front == ((self.end + 1) % self.size)); }