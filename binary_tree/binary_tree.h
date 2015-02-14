#ifndef BINARY_TREE__H
#define BINARY_TREE__H
/* namespace btree_ */

#include <stdbool.h>

typedef char datatype;

typedef struct _node
{
	datatype data;
	struct _node *left;
	struct _node *right;
} node;

typedef node * bin_tree;

void btree_init(bin_tree * root);
void btree_destroy(bin_tree root);

bin_tree btree_create_node(datatype value);
void btree_new(bin_tree * root, bin_tree left, bin_tree right, datatype value);

void btree_preorder_print(bin_tree root);
bool btree_node_is_leaf(bin_tree root);

int btree_get_depth(bin_tree root);
void btree_get_leaf_count(bin_tree root, int * leaf_num);

#endif