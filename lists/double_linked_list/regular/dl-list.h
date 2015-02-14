#ifndef DL_LIST__H
#define DL_LIST__H
/* namespace dl_list_ */

#include <stdbool.h>

typedef char datatype;

typedef struct _node
{
	datatype item;
	struct _node * next;
	struct _node * prev;
} node;

typedef node * list;

void dl_list_init(list * header);
void dl_list_destroy(list * header);

void dl_list_add_node(list * header, datatype value);
void dl_list_del_node(list * header, datatype value);

node * dl_list_seek_node(list header, datatype value);
int dl_list_count_nodes(list header);

bool dl_list_is_empty(list header);
void dl_list_print(list header); 

#endif