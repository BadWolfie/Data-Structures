#ifndef CIRCULAR_SIMPLE_LIST__H
#define CIRCULAR_SIMPLE_LIST__H

#include <stdbool.h>

typedef void * pointer;
typedef struct _CircularSimpleList CircularSimpleList;

CircularSimpleList * circular_simple_list_new (void);
void circular_simple_list_destroy (CircularSimpleList * self);

void circular_simple_list_add (CircularSimpleList * self, pointer value);
void circular_simple_list_del (CircularSimpleList * self, pointer value);

CircularSimpleList * circular_simple_list_find (CircularSimpleList * self, pointer value);
CircularSimpleList * circular_simple_list_get_last (CircularSimpleList * self);
int circular_simple_list_get_count (CircularSimpleList * self);

bool circular_simple_list_is_empty (CircularSimpleList * self);
bool circular_simple_list_has_one_node (CircularSimpleList * self);
void circular_simple_list_print (CircularSimpleList * self);

#endif
