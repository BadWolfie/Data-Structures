#include "dl-list.h"

#include <stdlib.h>
#include <stdio.h>

void dl_list_init(list * header)
{
	if (header) *header = NULL;
}

void dl_list_destroy(list * header)
{
	node * aux;
	for (aux = (*header); aux; aux = aux->next) {
		(*header) = aux->next;
		free(aux);
	}
}


void dl_list_add_node(list * header, datatype value)
{
	node * new_node = (node *) malloc(sizeof(node));
	new_node->item = value;
	new_node->next = (*header);
	new_node->prev = NULL;

	if (*header) (*header)->prev = new_node;
	(*header) = new_node;
}

void dl_list_del_node(list * header, datatype value)
{
	bool found = false;
	node * current = (*header);

	while (current && !found) {
		found = (current->item == value);
		if (!found) {
			current = current->next;
		}
	}

	if (found) {
		if (current == (*header)) {
			(*header) = current->next;
			current->next->prev = NULL;
		} else if (current->next) {
			current->prev->next = current->next;
			current->next->prev = current->prev;
		} else
			current->prev->next = NULL;

		free(current);
	} else
		puts("Node not found.");
}


node * dl_list_seek_node(list header, datatype value)
{
	list aux;
	for (aux = header; aux && (aux->item != value); aux = aux->next);
	return aux;
}

int dl_list_count_nodes(list header)
{
	list aux;
	int count = 0;

	for (aux = header; aux; aux = aux->next) count++;
	return count;
}

bool dl_list_is_empty(list header)
{ return header == NULL; }