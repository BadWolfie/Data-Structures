#ifndef CIRCULAR_LIST__H
#define CIRCULAR_LIST__H
/* namespace c_list_ */

#include <stdbool.h>

typedef char datatype;

typedef struct _node
{
	datatype data;
	struct _node * next;
} node;

typedef node * list;

void c_list_init(list * header);
void c_list_destroy(list * header);

void c_list_add_node(list * header, datatype value);
void c_list_del_node(list * header, datatype value);

node * c_list_seek_node(list header, datatype value);
node * c_list_seek_last_node(list header);
int c_list_count_nodes(list header);

bool c_list_is_empty(list header);
bool c_list_has_one_node(list header);
void c_list_print(list header);

#endif