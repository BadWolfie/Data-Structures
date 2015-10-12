#ifndef LIST__H
#define LIST__H

#include <stdbool.h>

typedef void * pointer;
typedef struct _List List;

List * doubly_list_new (void);
void doubly_list_destroy (List * self);

void doubly_list_add (List * self, pointer value);
void doubly_list_del (List * self, pointer value);

List * doubly_list_find (List * self, pointer value);
int doubly_list_get_count (List * self);

bool doubly_list_is_empty (List * self);
void doubly_list_print (List * self);

#endif
