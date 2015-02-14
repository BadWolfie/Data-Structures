#ifndef DL_CIRCULAR_LIST__H
#define DL_CIRCULAR_LIST__H
/* namespace dl_c_list_ */

#include <stdbool.h>

typedef char datatype;

typedef struct _node
{
	datatype data;
	struct _node * next;
	struct _node * prev;
} node;

typedef node * list;

void dl_c_list_init(list * header);
void dl_c_list_destroy(list * header);

void dl_c_list_add_node(list * header, datatype value);
void dl_c_list_del_node(list * header, datatype value);

node * dl_c_list_seek_node(list header, datatype value);
node * c_list_seek_last_node(list header);
int dl_c_list_count_nodes(list header);

bool dl_c_list_is_empty(list header);
bool dl_c_list_has_one_node(list header);

#endif