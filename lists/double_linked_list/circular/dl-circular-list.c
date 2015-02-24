#include "dl-circular-list.h"

#include <stdlib.h>
#include <stdio.h>

void dl_c_list_init(list * header)
{
	if (*header) *header = NULL;
}

void dl_c_list_destroy(list * header)
{
	node * aux;
	for (aux = (*header); aux->next != (*header); aux = aux->next) {
		(*header) = aux->next;
		free(aux);
	}
}


void dl_c_list_add_node(list * header, datatype value)
{
	node * new_node = (node *) malloc(sizeof(node));
	new_node->data = value;
	new_node->next = new_node;
	new_node->prev = new_node;

	if (*header) {
		(*header)->prev->next = new_node;
		new_node->prev = (*header)->prev;

		new_node->next = (*header);
		(*header)->prev = new_node;
	}
	
	(*header) = new_node;
}

void dl_c_list_del_node(list * header, datatype value)
{
	bool found = false;
	node * current = (*header);

	while ((current->next != (*header)) && !found) {
		found = (current->data == value);
		if (!found)
			current = current->next;
	}

	if (found) {
		current->next->prev = current->prev;
		current->prev->next = current->next;
		free(current);
	} else
		puts("Node not found.");
}


node * dl_c_list_seek_node(list header, datatype value)
{
	list aux;
	for (aux = header; (aux->next != header) && 
			(aux->data != value); aux = aux->next);
	return aux;
}

int dl_c_list_count_nodes(list header)
{
	list aux;
	int count = 0;

	for (aux = header; aux->next != header; aux = aux->next) count++;
	return count;
}

bool dl_c_list_is_empty(list header)
{ return header == NULL; }

bool dl_c_list_has_one_node(list header)
{ return (header->next == header); }

void dl_c_list_print(list header)
{
	list aux;
	for (aux = header; aux->next != header; aux = aux->next)
		;// print(data); // How to print it depends on its type. 
}