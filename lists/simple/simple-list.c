#include "simple-list.h"

#include <stdlib.h>
#include <stdio.h>

struct _SimpleList
{
  pointer data;
  SimpleList * next;
};

SimpleList *
simple_list_new (void)
{
  return NULL;
}

void
simple_list_destroy (SimpleList * self)
{
  SimpleList * aux;
  for (aux = self; aux; aux = aux->next) {
    self = aux->next;
    free(aux);
  }
}


void
simple_list_add (SimpleList * self, pointer value)
{
  SimpleList * new_node = (SimpleList *) malloc(sizeof(SimpleList));
  new_node->data = value;
  new_node->next = self;
  self = new_node;
}

void
simple_list_del (SimpleList * self, pointer value)
{
  SimpleList * current = self;
  SimpleList * previous = NULL;

  bool found = false;
  while (current && !found) {
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


SimpleList *
simple_list_find (SimpleList * self, pointer value)
{
  SimpleList * aux;
  for (aux = self; aux && (aux->data != value); aux = aux->next);
  return aux;
}

int
simple_list_count (SimpleList * self)
{
  SimpleList * aux;
  int count = 0;

  for (aux = self; aux; aux = aux->next) count++;
  return count;
}

bool
simple_list_is_empty (SimpleList * self)
{
  return self == NULL;
}

void
simple_list_print (SimpleList * self)
{
  SimpleList * aux;
  for (aux = self; aux; aux = aux->next) {
    ;// print(data); // How to print it depends on its type.
  }
}
