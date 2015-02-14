#include "binary_tree.h"

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