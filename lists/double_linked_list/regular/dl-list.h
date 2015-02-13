#ifndef LIST__H
#define LIST__H
/* namespace list_ */

#include <stdbool.h>

typedef struct _node
{
	datatype item;
	struct _node * next;
	struct _node * prev;
} node;

typedef node * list;

void list_init(list * header);
void list_destroy(list * header);

void list_add_node(list * header, datatype value);
void list_del_node(list * header, datatype value);

node * list_seek_node(list header, datatype value);
int list_count_nodes(list header);
bool list_is_empty(list header);

#endif