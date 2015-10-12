#ifndef CIRCULAR_LIST__H
#define CIRCULAR_LIST__H

#include <stdbool.h>

typedef void * pointer;
typedef struct _CircularList CircularList;

CircularList * circular_list_new (void);
void circular_list_destroy (CircularList * self);

void circular_list_add (CircularList * self, pointer value);
void circular_list_del (CircularList * self, pointer value);

CircularList * circular_list_find (CircularList * self, pointer value);
int circular_list_get_count (CircularList * self);

bool circular_list_is_empty (CircularList * self);
bool circular_list_has_one_node (CircularList * self);
void circular_list_print (CircularList * self);

#endif
