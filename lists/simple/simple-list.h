#ifndef SIMPLE_LIST__H
#define SIMPLE_LIST__H

#include <stdbool.h>

typedef void * pointer;
typedef struct _SimpleList SimpleList;

SimpleList * simple_list_new (void);
void simple_list_destroy (SimpleList * self);

void simple_list_add (SimpleList * self, pointer value);
void simple_list_del (SimpleList * self, pointer value);

SimpleList * simple_list_find (SimpleList * self, pointer value);
int simple_list_count (SimpleList * self);

bool simple_list_is_empty (SimpleList * self);
void simple_list_print (SimpleList * self);

#endif
