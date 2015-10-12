#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

struct _Queue
{
	pointer * data;
	int size;
  int front;
  int end;
};

Queue *
queue_new (int size)
{
  Queue * self = (Queue *) malloc(sizeof(Queue));
	self->data = (pointer *) malloc(size * sizeof(pointer));
	self->front = self-> end = 0;
	self->size = size;
  return self;
}

void
queue_destroy (Queue * self)
{
	free(self->data);
	self->front = self-> end = 0;
}

void
queue_reset (Queue * self)
{
	free(self->data);
	self = queue_new(self->size);
}


void
queue_push (Queue * self, pointer value)
{
	if (queue_is_full(self)) {
		puts("Queue is full.");
		exit(1);
	}

	self->end = (self->end + 1) % self->size;
	self->data[self->end] = value;
}

pointer
queue_pop (Queue * self)
{
	if (queue_is_empty(self)) {
		puts("Queue is empty.");
		exit(1);
	}

	self->front = (self->front + 1) % self->size;
	return self->data[self->front];
}

pointer
queue_get_data_at_front (const Queue * self)
{
	if (queue_is_empty(self)) {
		puts("Queue is empty.");
		exit(1);
	}

	return self->data[self->front];
}


bool
queue_is_empty (const Queue * self)
{
  return (self->front == self->end);
}

bool
queue_is_full (const Queue * self)
{
  return (self->front == ((self->end + 1) % self->size));
}

