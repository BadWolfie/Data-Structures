/* List.h
 *
 * Header file for List, a standard doubly-linked list library based on the GLib
 * implementation of doubly-linked lists, the GList structure and its associated
 * functions, see:
 * https://developer.gnome.org/glib/stable/glib-Doubly-Linked-Lists.html
 *
 * Copyright (c) 2016 Ian Hernandez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef LIST__H
#define LIST__H

#include <stdbool.h>

/*    Data types    */
/** The struct used for each node in a doubly-linked list. */
typedef struct _List List;

/**
 * Specifies the type of a comparison function used to compare two values.
 * The function should return a negative integer if the first value comes before
 * the second, 0 if they are equal, or a positive integer if the first value
 * comes after the second.
 *
 * It's used internally by list_find_custom().
 *
 * @param a A value.
 * @param b A value to compare 'a' with.
 * @param param_data Additional data needed for the comparison.
 * @return A negative value if 'a < b', zero if 'a = b', positive value if
 *    'a > b'.
 */
typedef int (*CompareFunction) (const void * a,
                                const void * b,
                                void * param_data);

/**
 * Specifies the type of a copy function used to copy the node data when doing a
 * full-copy of a list.
 *
 * It's used internally by list_full_copy().
 *
 * @param original A pointer to the data to be copied.
 * @param param_data Additional data needed for the copying process.
 * @return A pointer to the copy.
 */
typedef void * (*CopyFunction) (const void * original, void * param_data);

/**
 * Specifies the type of a function that will be executed once for every node in
 * the list, it can do anything that the user wants.
 *
 * It's used internally by list_foreach().
 *
 * @param node_data The list node data.
 * @param param_data Additional data used by the ForeachFunction when its called.
 */
typedef void (*ForeachFunction) (void * node_data, void * param_data);

/**
 * Specifies the type of a function that takes the data from a List node and
 * creates a printable string from it.
 *
 * It's used internally by list_node_to_string().
 *
 * @param node_data The list node data.
 * @param param_data Additional data needed for string formatting, it could be
 *    NULL if none needed.
 * @return The list node data string representation.
 */
typedef const char * (*ToStringFunction) (void * node_data, void * param_data);

/**
 * Specifies the type of function which is called when a node's data is
 * destroyed. It is passed the pointer to the data element and should free any
 * memory and resources allocated for it.
 *
 * It's used internally by list_full_destroy().
 *
 * @param node_data The data element.
 */
typedef void (*DestroyFunction) (void * node_data);

#ifdef __cplusplus /*    C++ support    */
extern "C" {
#endif

/*    Function prototypes    */
/**
 * "Creates" a list, calling this is optional since NULL is considered to be a
 * valid empty list, you could simply set a 'List *' to NULL to initialize it.
 *
 * @return NULL
 */
List * list_new (void);

/**
 * Allocates space for one List node.
 *
 * @return A pointer to the newly-allocated List node.
 */
List * list_node_alloc (void);

/**
 * Frees all of the memory used by a List. If list nodes contain
 * dynamically-allocated memory, you should either use list_full_destroy() or
 * free them manually first.
 *
 * @param self A pointer to a List.
 */
void list_destroy (List * self);

/**
 * Frees all the memory used by a List, and calls free_func on every node's data.
 *
 * @param self A pointer to a List.
 * @param free_func The function to be called to free each node's data.
 */
void list_full_destroy (List * self, DestroyFunction free_func);

/**
 * Adds a new node on to the end of the list. Note that the return value is
 * the new start of the list, if list was empty; make sure you store the new
 * value.
 *
 * @param self A pointer to a List.
 * @param node_data The data of the new node.
 * @return Either 'self' or the new start of the List if 'self' was NULL.
 */
List * list_append (List * self, void * node_data);

/**
 * Prepends a new node on to the start of the list. Note that the return
 * value is the new start of the list, which will have changed, so make sure you
 * store the new value.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param node_data The data of the new node.
 * @return A pointer to the newly prepended node, which is the new start of
 *    the List.
 */
List * list_prepend (List * self, void * node_data);

/**
 * Inserts a new node into the list at the given position.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param node_data The data of the new node.
 * @param position The position to insert the node. If this is negative, or
 *    is larger than the number of nodes in the list, the new node is
 *    added on to the end of the list.
 * @return The (possibly changed) start of the List.
 */
List * list_insert (List * self, void * node_data, int position);

/**
 * Inserts a new node into the list before the given position.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param node The list node before which the new node is inserted or NULL
 *    to insert at the end of the list.
 * @param node_data The data of the new node.
 * @return The (possibly changed) start of the List.
 */
List * list_insert_before (List * self, List * node, void * node_data);

/**
 * Inserts a new node into the list after the given position.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param node The list node after which the new node is inserted or NULL
 *    to insert at the start of the list.
 * @param node_data The data of the new node.
 * @return The (possibly changed) start of the List.
 */
List * list_insert_after (List * self, List * node, void * node_data);

/**
 * Removes a node from a List. If two nodes contain the same data, only
 * the first is removed. If none of the nodes contain the data, the List is
 * unchanged.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param node_data The data of the node to remove.
 * @return The (possibly changed) start of the List.
 */
List * list_remove (List * self, const void * node_data);

/**
 * Removes all list nodes with data equal to 'node_data'. Returns the new head
 * of the list. Contrast with list_remove() which removes only the first node
 * matching the given data.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param node_data The data to remove.
 * @return The (possibly changed) start of the List.
 */
List * list_remove_all (List * self, const void * node_data);

/**
 * Removes a node from a List, without freeing the node. The removed node's prev
 * and next links are set to NULL, so that it becomes a self-contained list with
 * one node.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param link An element in the List.
 * @return The (possibly changed) start of the List.
 */
List * list_remove_link (List * self, List * link);

/**
 * Gets the first node in a List.
 *
 * @param self A pointer to any node in a List.
 * @return The first node in the List, or NULL if the List has no nodes.
 */
List * list_get_first (const List * self);

/**
 * Gets the last node in a List.
 *
 * @param self A pointer to any node in a List.
 * @return The last node in the List, or NULL if the List has no nodes.
 */
List * list_get_last (const List * self);

/**
 * Gets the previous node in a List.
 *
 * @param self A pointer to a List node.
 * @return The previous node, or NULL if there are no previous nodes.
 */
List * list_get_previous (const List * self);

/**
 * Gets the next node in a List.
 *
 * @param self A pointer to a List node.
 * @return The next node, or NULL if there are no more nodes.
 */
List * list_get_next (const List * self);

/**
 * Gets the node at the given position in a List.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param n The position of the node, counting from zero.
 * @return The node, or NULL if the position is off the end of the List.
 */
List * list_get_node_at (const List * self, unsigned int n);

/**
 * Finds the node in a List which contains the given data.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param node_data The node data to be found.
 * @return The found List node, or NULL if it's not found.
 */
List * list_find (const List * self, const void * node_data);

/**
 * Finds a node in a List, using a supplied function to find the desired
 * node. It iterates over the list, calling the given function which should
 * return 0 when the desired node is found. The function takes two arguments,
 * the List node's data as the first argument and the given user data.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param node_data The node data to be found.
 * @param func The function to call for each node. It should return 0 when the
 *    desired node is found.
 * @return The found List node, or NULL if it's not found.
 */
List * list_find_custom (const List * self,
                         const void * node_data,
                         CompareFunction func);

/**
 * Copies a List.
 * Note that this is a "shallow" copy. If the list nodes consist of pointers to
 * data, the pointers are copied but the actual data is not. See list_full_copy()
 * if you need to copy the data as well.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @return The start of the new list that holds the same data as 'self'.
 */
List * list_copy (List * self);

/**
 * Makes a full copy of a List.
 * In contrast with list_copy(), this function uses 'func' to make a copy of
 * each list node, in addition to copying the list container itself.
 *
 * 'func', as a CopyFunction, takes two arguments, the data to be copied and a
 * 'param_data' pointer. It's safe to pass NULL as param_data, if the copy
 * function takes only one argument.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param func A  copy function used to copy every node in the list.
 * @param param_data
 * @return
 */
List * list_full_copy (List * self, CopyFunction func, void * param_data);

/**
 * Reverses a List. It simply switches the next and prev pointers of each node.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @return The start of the reversed List.
 */
List * list_reverse (List * self);

/**
 * Adds the second List onto the end of the first List. Note that the nodes of
 * the second List are not copied, they are used directly.
 *
 * @param list1 A List, this must point to the top of the list.
 * @param list2 The List to add to the end of the first List, this must point to
 *    the top of the list.
 * @return The start of the new List, which equals 'list1' if not NULL.
 */
List * list_concat (List * list1, List * list2);

/**
 * Calls a function for each element of a List.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param func The function to call with each node's data.
 * @param param_data Extra data that the function needs.
 */
void list_foreach (const List * self, ForeachFunction func, void * param_data);

/**
 * Gets the position of the node containing the given data (starting from zero).
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @param data The data to find.
 * @return The index of the node containing the data, or -1 if the data is not
 *    found.
 */
int list_get_index (const List * self, const void * data);

/**
 * Gets the number of nodes in a List.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @return The number of nodes in the List.
 */
unsigned int list_get_length (const List * self);

/**
 * Gets the data of the given node.
 *
 * @param self A pointer to a List node.
 * @return The node's data.
 */
void * list_get_data (const List * self);

/**
 * Checks if 'self' is empty an empty list, calling this is optional since you
 * could just compare a 'List *' to NULL to see if it's empty.
 *
 * @param self A pointer to a List, this must point to the top of the list.
 * @return Whether or not the list is empty.
 */
bool list_is_empty (const List * self);

/**
 * Checks if 'self' is the first node in a list.
 *
 * @param self A pointer to a List node.
 * @return Whether or not the node is the first in the list.
 */
bool list_is_first (const List * self);

/**
 * Checks if 'self' is the last node in a list.
 *
 * @param self A pointer to a List node.
 * @return Whether or not the node is the last in the list.
 */
bool list_is_last (const List * self);

/**
 *
 * @param self A pointer to a List node.
 * @param func "To-string" function, it must take the data from the node and
 *    create a string representation for it.
 * @param param_data Additional data needed for string formatting, it could be
 *    NULL if none needed.
 * @return The list node data string representation.
 */
const char * list_node_to_string (const List * self,
                                  ToStringFunction func,
                                  void * param_data);

#ifdef __cplusplus
}
#endif

#endif /* LIST__H */
