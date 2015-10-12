#include "circular-list.h"

#include <stdlib.h>
#include <stdio.h>

struct _CircularList
{
  pointer data;
  CircularList * next;
  CircularList * prev;
};

CircularList *
circular_list_new (void)
{
  return NULL;
}

void
circular_list_destroy (CircularList * self)
{
  CircularList * aux;
  for (aux = self; aux->next != self; aux = aux->next) {
    self = aux->next;
    free(aux);
  }
}


void
circular_list_add (CircularList * self, pointer value)
{
  CircularList * new_node = (CircularList *) malloc(sizeof(CircularList));
  new_node->data = value;
  new_node->next = new_node;
  new_node->prev = new_node;

  if (self) {
    self->prev->next = new_node;
    new_node->prev = self->prev;

    new_node->next = self;
    self->prev = new_node;
  }

  self = new_node;
}

void
circular_list_del (CircularList * self, pointer value)
{
  bool found = false;
  CircularList * current = self;

  while ((current->next != self) && !found) {
    found = (current->data == value);
    if (!found)
      current = current->next;
  }

  if (found) {
    current->next->prev = current->prev;
    current->prev->next = current->next;
    free(current);
  } else
    puts("Node not found.");
}


CircularList *
circular_list_find (CircularList * self, pointer value)
{
  CircularList * aux;
  for (aux = self; (aux->next != self) &&
      (aux->data != value); aux = aux->next);
  return aux;
}

int
circular_list_get_count (CircularList * self)
{
  CircularList * aux;
  int count = 0;

  for (aux = self; aux->next != self; aux = aux->next) count++;
  return count;
}

bool
circular_list_is_empty (CircularList * self)
{
  return self == NULL;
}

bool
circular_list_has_one_node (CircularList * self)
{
  return (self->next == self);
}

void
circular_list_print (CircularList * self)
{
  CircularList * aux;
  for (aux = self; aux->next != self; aux = aux->next) {
    ;// print(data); // How to print it depends on its type.
  }
}
