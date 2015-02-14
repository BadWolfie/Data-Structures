#include "list.h"

#include <stdlib.h>
#include <stdio.h>

void list_init(list * header)
{
	if (header) *header = NULL;
}

void list_destroy(list * header)
{
	node * aux;
	for (aux = (*header); aux; aux = aux->next) {
		(*header) = aux->next;
		free(aux);
	}
}


void list_add_node(list * header, datatype value)
{
	node * new_node = (node *) malloc(sizeof(node));
	new_node->data = value;
	new_node->next = (*header);
	(*header) = new_node;
}

void list_del_node(list * header, datatype value)
{
	node * current = (*header);
	node * previous = NULL;

	bool found = false;
	while (current && !found) {
		found = (current->data == value);
		if (!found) {
			previous = current;
			current = current->next;
		}
	}

	if (found) {
		if (current == (*header))
			(*header) = current->next;
		else
			previous->next = current->next;
		free(current);
	} else
		puts("Node not found.");
}


node * list_seek_node(list header, datatype value)
{
	list aux;
	for (aux = header; aux && (aux->data != value); aux = aux->next);
	return aux;
}

int list_count_nodes(list header)
{
	list aux;
	int count = 0;

	for (aux = header; aux; aux = aux->next) count++;
	return count;
}

bool list_is_empty(list header)
{ return header == NULL; }