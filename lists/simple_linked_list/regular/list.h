#ifndef LIST__H
#define LIST__H
/* namespace list_ */

#include <stdbool.h>

typedef char datatype;

typedef struct _node
{
	datatype data;
	struct _node * next;
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