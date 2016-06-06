/* List.c
 *
 * Copyright (c) 2016 Ian Hernandez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <stdlib.h>

#include "List.h"

struct _List
{
  /** Holds the node's data, which can be a pointer to any kind of data. */
  void * data;

  /** Contains the link to the previuos node in the list. */
  List * prev;

  /** Contains the link to the next node in the list. */
  List * next;
};

List *
list_new (void)
{
  return NULL;
}

List *
list_node_alloc (void)
{
  List * self = (List *) malloc (sizeof(List));
  self->data = NULL;
  self->prev = NULL;
  self->next = NULL;
  return self;
}

void
list_destroy (List * self)
{
  if (self == NULL)
    return;

  list_destroy (self->next);
  free (self);
}

void
list_full_destroy (List * self, DestroyFunction free_func)
{
  list_foreach (self, (ForeachFunction) free_func, NULL);
  list_destroy (self);
}

List *
list_append (List * self, void * node_data)
{
  List * new_node;
  List * last_node;

  new_node = list_node_alloc ();
  new_node->data = node_data;

  if (self != NULL) {
    last_node = list_get_last (self);
    last_node->next = new_node;
    new_node->prev = last_node;
    return self;
  }

  return new_node;
}

List *
list_prepend (List * self, void * node_data)
{
  List * new_node;

  new_node = list_node_alloc ();
  new_node->data = node_data;
  new_node->next = self;

  if (self != NULL) {
    self->prev = new_node;
  }

  return new_node;
}

List *
list_insert (List * self, void * node_data, int position)
{
  List * new_node;
  List * aux_node;

  if (position < 0)
    return list_append (self, node_data);

  if (position == 0)
    return list_prepend (self, node_data);

  aux_node = list_get_node_at (self, position);
  if (aux_node == NULL)
    return list_append (self, node_data);

  new_node = list_node_alloc ();
  new_node->data = node_data;
  new_node->prev = aux_node->prev;
  new_node->next = aux_node;

  aux_node->prev->next = new_node;
  aux_node->prev = new_node;
  return self;
}

List *
list_insert_before (List * self, List * node, void * node_data)
{
  if (self == NULL) {
    self = list_node_alloc ();
    self->data = node_data;
    return self;
  }

  if (node == NULL) {
    return list_append (self, node_data);
  }

  List * new_node;
  new_node = list_node_alloc ();
  new_node->data = node_data;
  new_node->prev = node->prev;
  new_node->next = node;

  node->prev = new_node;
  if (node->prev != NULL) {
    node->prev->next = new_node;
    return self;
  }

  return new_node;
}

List *
list_insert_after (List * self, List * node, void * node_data)
{
  if (self == NULL) {
    self = list_node_alloc ();
    self->data = node_data;
    return self;
  }

  if (node == NULL) {
    return list_prepend (self, node_data);
  }

  List * new_node;
  new_node = list_node_alloc ();
  new_node->data = node_data;
  new_node->prev = node;
  new_node->next = node->next;

  node->next = node;
  if (node->next != NULL) {
    node->next->prev = new_node;
  }

  return self;
}

List *
list_remove (List * self, const void * node_data)
{
  List * tmp = list_find (self, node_data);
  if (tmp != NULL) {
    self = list_remove_link (self, tmp);
    list_destroy (tmp);
  }

  return self;
}

List *
list_remove_all (List * self, const void * node_data)
{
  List * tmp;
  tmp = list_find (self, node_data);

  while (tmp != NULL) {
    self = list_remove_link (self, tmp);
    list_destroy (tmp);

    tmp = list_find (self, node_data);
  }

  return self;
}

List *
list_remove_link (List * self, List * link)
{
  if (self == NULL)
    return NULL;

  if (link->prev != NULL)
    link->prev->next = link->next;

  if (link->next != NULL)
    link->next->prev = link->prev;

  if (link == self)
    self = self->next;

  link->prev = NULL;
  link->next = NULL;

  return self;
}

List *
list_get_first (const List * self)
{
  if (self == NULL)
    return NULL;

  List * iterator = (List *) self;
  while (iterator->prev != NULL)
    iterator = iterator->prev;
  return iterator;
}

List *
list_get_last (const List * self)
{
  if (self == NULL)
    return NULL;

  List * iterator = (List *) self;
  while (iterator->next != NULL)
    iterator = iterator->next;
  return iterator;
}

List *
list_get_previous (const List * self)
{
  return self->prev;
}

List *
list_get_next (const List * self)
{
  return self->next;
}

List *
list_get_node_at (const List * self, unsigned int n)
{
  List * iterator = (List *) self;

  while ( ( (n--) > 0) && (iterator != NULL)) {
    iterator = iterator->next;
  }

  return iterator;
}

List *
list_find (const List * self, const void * node_data)
{
  List * iterator = (List *) self;
  while (iterator != NULL) {
    if (iterator->data == node_data)
      break;
    iterator = iterator->next;
  }

  return iterator;
}

List *
list_find_custom (const List * self,
                  const void * node_data,
                  CompareFunction func)
{
  if (func == NULL)
    return (List *) self;

  List * iterator = (List *) self;
  int comparison;

  while (iterator != NULL) {
    comparison = func (iterator->data, node_data, NULL);
    if (comparison == 0)
      break;
    iterator = iterator->next;
  }

  return iterator;
}

List *
list_copy (List * self)
{
  return list_full_copy (self, NULL, NULL);
}

List *
list_full_copy (List * self, CopyFunction func, void * param_data)
{
  List * iterator = self;
  List * copy = NULL;
  List * new_node;

  while (iterator != NULL) {
    new_node = list_node_alloc ();

    if (func != NULL)
      new_node->data = func (iterator->data, param_data);
    else
      new_node->data = iterator->data;
    copy = list_append (copy, new_node);

    iterator = iterator->next;
  }

  return copy;
}

List *
list_reverse (List * self)
{
  List * aux = NULL;

  while (self != NULL) {
    aux = self;
    self = aux->next;
    aux->next = aux->prev;
    aux->prev = self;
  }

  return aux;
}

List *
list_concat (List * list1, List * list2)
{
  List * last;

  if (list2 == NULL) {
    last = list_get_last (list1);

    if (last != NULL)
      last->next = list2;
    else
      last = list2;
    list2->prev = last;
  }

  return list1;
}

void
list_foreach (const List * self, ForeachFunction func, void * param_data)
{
  List * iterator = (List *) self;

  while (iterator != NULL) {
    func (iterator->data, param_data);
    iterator = iterator->next;
  }
}

int
list_get_index (const List * self, const void * data)
{
  unsigned int count = 0;
  List * iterator = (List *) self;

  while (iterator != NULL) {
    if (iterator->data == data)
      return count;

    iterator = iterator->next;
    count += 1;
  }

  return -1;
}

unsigned int
list_get_length (const List * self)
{
  unsigned int count = 0;
  List * iterator = (List *) self;

  while (iterator != NULL) {
    iterator = iterator->next;
    count += 1;
  }

  return count;
}

void *
list_get_data (const List * self)
{
  return self->data;
}

bool
list_is_empty (const List * self)
{
  return (self == NULL);
}

bool
list_is_first (const List * self)
{
  return (self->prev == NULL);
}

bool
list_is_last (const List * self)
{
  return (self->next == NULL);
}

const char *
list_node_to_string (const List * self,
                     ToStringFunction func,
                     void * param_data)
{
  if (self == NULL)
    return NULL;

  return func (self->data, param_data);
}
