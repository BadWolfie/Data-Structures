#include "binary-tree.h"

#include <stdlib.h>
#include <stdio.h>

void btree_init(bin_tree * root)
{
	if (*root) *root = NULL;
}

void btree_destroy(bin_tree root)
{
	if (root) {
		btree_destroy(root->left);
		btree_destroy(root->right);
		free(root);
	}
}


bin_tree btree_create_node(datatype value)
{
	bin_tree new_node = (bin_tree) malloc(sizeof(node));
	new_node->data = value;
	new_node->left = new_node->right = NULL;
	return new_node;
}

void btree_new(bin_tree * root, bin_tree left, bin_tree right, datatype value)
{
	*root = btree_create_node(value);
	(*root)->left = left;
	(*root)->right = right;
}


void btree_preorder_print(bin_tree root)
{
	if (root) {
		// print(data); // How to print it depends on its type.
		btree_preorder_print(root->left);
		btree_preorder_print(root->right);
	}
}

bool btree_node_is_leaf(bin_tree root)
{ return (!root->left && !root->right); }


int btree_get_depth(bin_tree root)
{
	if (!root)
		return 0;
	int depth_left, depth_right;
	depth_left = btree_get_depth(root->left);
	depth_right = btree_get_depth(root->right);

	if (depth_left > depth_right)
		return (depth_left + 1);
	return (depth_right + 1);
}

void btree_get_leaf_count(bin_tree root, int * leaf_num)
{
	if (root) {
		btree_get_leaf_count(root->left, leaf_num);
		btree_get_leaf_count(root->right, leaf_num);
		if (btree_node_is_leaf(root)) (*leaf_num)++;
	}
}


/* Ordered binary tree functions. */
void btree_add_node(bin_tree * root, datatype value)
{
	if (!(*root))
		*root = btree_create_node(value);
	else if ((*root)->data > value) // Comparison depends on data type
		btree_add_node(&((*root)->left),value);
	else
		btree_add_node(&((*root)->right),value);
}

bin_tree btree_seek_node(bin_tree root, datatype value)
{
	if (!root)
		return NULL;
	if (root->data == value)
		return root;
	if (root->data > value)
		return btree_seek_node(root->left,value);
	else
		return btree_seek_node(root->right,value);
}

void btree_del_node(bin_tree * root, datatype value)
{
	if (!(*root)) {
		puts("Node not found.");
		return;
	}

	if (value < (*root)->data)
		btree_del_node(&((*root)->left),value);
	if (value > (*root)->data)
		btree_del_node(&((*root)->right),value);

	if (value == (*root)->data) {
		bin_tree aux = *root;

		if (!aux->left)
			(*root) = aux->right;
		else if (!aux->right)
			(*root) = aux->left;
		else
			btree_replace(&aux);

		free(aux);
	}
}

void btree_replace(bin_tree * self)
{
	bin_tree a, p;
	p = *self;
	a = (*self)->left;

	while (a->right) {
		p = a;
		a = a->right;
	}

	(*self)->data = a->data;
	if (p == (*self))
		p->left = a->left;
	else
		p->right = a->left;

	(*self) = a;
}
