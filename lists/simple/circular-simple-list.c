#include "circular-simple-list.h"

#include <stdlib.h>
#include <stdio.h>

struct _CircularSimpleList
{
  pointer data;
  CircularSimpleList * next;
};

CircularSimpleList *
circular_simple_list_new (void)
{
  return NULL;
}

void
circular_simple_list_destroy (CircularSimpleList * self)
{
  CircularSimpleList * aux;
  for (aux = self; aux->next != self; aux = aux->next) {
    self = aux->next;
    free(aux);
  }
}


void
circular_simple_list_add (CircularSimpleList * self, pointer value)
{
  CircularSimpleList * new_node = (CircularSimpleList *) malloc(sizeof(CircularSimpleList));
  new_node->data = value;
  new_node->next = new_node;

  if (self) {
    CircularSimpleList * aux = circular_simple_list_get_last(self);
    new_node->next = self;
    aux->next = new_node;
  }

  self = new_node;
}

void
circular_simple_list_del (CircularSimpleList * self, pointer value)
{
  CircularSimpleList * current = self;
  CircularSimpleList * previous = NULL;

  bool found = false;
  while ((current->next != self) && !found) {
    found = (current->data == value);
    if (!found) {
      previous = current;
      current = current->next;
    }
  }

  if (found) {
    if (current == self)
      self = current->next;
    else
      previous->next = current->next;
    free(current);
  } else
    puts("Node not found.");
}


CircularSimpleList *
circular_simple_list_find (CircularSimpleList * self, pointer value)
{
  CircularSimpleList * aux;
  for (aux = self; (aux->next != self) && (aux->data != value); aux = aux->next);
  return aux;
}

CircularSimpleList *
circular_simple_list_get_last (CircularSimpleList * self)
{
  CircularSimpleList * aux;
  for (aux = self; aux->next != self; aux = aux->next);
  return aux;
}

int
circular_simple_list_get_count (CircularSimpleList * self)
{
  CircularSimpleList * aux;
  int count = 0;

  for (aux = self; aux->next != self; aux = aux->next) count++;
  return count;
}


bool
circular_simple_list_is_empty (CircularSimpleList * self)
{
  return self == NULL;
}

bool
circular_simple_list_has_one_node (CircularSimpleList * self)
{
  return (self->next == self);
}

void
circular_simple_list_print (CircularSimpleList * self)
{
  CircularSimpleList * aux;
  for (aux = self; aux->next != self; aux = aux->next) {
    ;// print(data); // How to print it depends on its type.
  }
}
