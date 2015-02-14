#include "dl-circular-list.h"

#include <stdlib.h>
#include <stdio.h>

void dl_c_list_init(list * header)
{
	if (header) *header = NULL;
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
		node * aux = c_list_seek_last_node(*header);
		aux->next = new_node;
		new_node->prev = aux;
		
		new_node->next = (*header);
		(*header)->prev = new_node;
	}
	
	(*header) = new_node;
}

void dl_c_list_del_node(list * header, datatype value)
{
	node * current = (*header);
	bool found = false;

	while ((current->next != (*header)) && !found) {
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


node * dl_c_list_seek_node(list header, datatype value)
{
	list aux;
	for (aux = header; (aux->next != header) && 
			(aux->data != value); aux = aux->next);
	return aux;
}

node * c_list_seek_last_node(list header)
{
	list aux;
	for (aux = header; aux->next != header; aux = aux->next);
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