#include "list.h"

#include <stdlib.h>
#include <stdio.h>

struct _List
{
	pointer data;
	List * next;
	List * prev;
};

List *
doubly_list_new (void)
{
	return NULL;
}

void
doubly_list_destroy (List * self)
{
	List * aux;
	for (aux = self; aux; aux = aux->next) {
		self = aux->next;
		free(aux);
	}
}


void
doubly_list_add (List * self, pointer value)
{
	List * new_node = (List *) malloc(sizeof(List));
	new_node->data = value;
	new_node->next = self;
	new_node->prev = NULL;

	if (self)
    self->prev = new_node;
	self = new_node;
}

void
doubly_list_del (List * self, pointer value)
{
	bool found = false;
	List * current = self;

	while (current && !found) {
		found = (current->data == value);
		if (!found)
			current = current->next;
	}

	if (found) {
		if (current == self) {
			self = current->next;
			current->next->prev = NULL;
		} else if (current->next) {
			current->prev->next = current->next;
			current->next->prev = current->prev;
		} else
			current->prev->next = NULL;

		free(current);
	} else
		puts("Node not found.");
}


List *
doubly_list_find (List * self, pointer value)
{
	List * aux;
	for (aux = self; aux && (aux->data != value); aux = aux->next);
	return aux;
}

int
doubly_list_get_count (List * self)
{
	List * aux;
	int count = 0;

	for (aux = self; aux; aux = aux->next) count++;
	return count;
}


bool
doubly_list_is_empty (List * self)
{
  return self == NULL;
}

void
doubly_list_print (List * self)
{
	List * aux;
	for (aux = self; aux; aux = aux->next) {
		;// print(data); // How to print it depends on its type. 
  }
}
