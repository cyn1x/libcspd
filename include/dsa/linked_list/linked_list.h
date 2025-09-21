/**
 * @file linked_list.h
 */

/**
 * @def print_llist(type, llist, reverse)
 *
 * @brief Prints the contents of the linked list.
 *
 * Basic print function for C types residing in a linked list by casting each
 * element to the specified type. The linked list can be printed in reverse if
 * instructed.
 *
 * @param type Type of data to be casted.
 * @param llist The linked list to be printed out.
 * @param reverse Boolean to control order of printing.
 */

/**
 * @typedef struct llist_node
 *
 * @brief Data structure for linked list nodes.
 *
 * @var llist_node::data
 * Memory which has been allocated for the linked list node to store data.
 *
 * @var linked_list::prev
 * Pointer to the previous node in the linked list.
 *
 * @var linked_list::next
 * Pointer to the next node in the linked list.
 */

/**
 * @typedef struct llist_t
 *
 * @brief Data structure for linked list.
 *
 * @var llist::data_size
 * The size of the data in bytes being stored in the linked list nodes.
 *
 * @var llist::head
 * Pointer to the first node in the linked list.
 *
 * @var llisit::tail
 * Pointer to the last node in the linked list.
 *
 * @var lllist::_cmp
 * Comparator function used for sorting or searching. The library contains some
 * basic types as seen below, which can be assigned to the `_cmp` variable. You
 * can also provide your own comparator functions.
 *
 * @b Example
 * The provided comparator functions can be defined in a header file.
 *
 * @include defs.test.h
 * Once defined, assign the address of the defined functions from the header
 * file to the comparator function pointer.
 *
 * @snippet linked_list.test.c Comparator function
 */

/**
 * @fn void llist_init(llist_t *llist, size_t data_size)
 *
 * @brief Initializes a new linked list.
 *
 * Sets `data_size` to the given parameter, and sets the head and tail pointers
 * to `NULL`.
 *
 * @param vec Pointer to the linked list to be initialized.
 * @param data_size The size of the data type in bytes.
 *
 * @returns void
 *
 * @b Example
 * @snippet linked_list.test.c Initialize
 */

/**
 * @fn node *node_init(llist_t *llist)
 *
 * @brief Initializes a new node.
 *
 * Memory is allocated for the new node and the data that will reside within the
 * new node structure. The `prev` and `next` pointers are set to `NULL`.
 *
 * @param llist Pointer to the linked list structure.
 *
 * @returns Pointer to the new node in memory.
 *
 * @b Example
 * @snippet linked_list.test.c Initialize
 */

/**
 * @fn void llist_append(llist_t *llist, void *data)
 *
 * @brief Adds a node to the end of the linked list.
 *
 * Initializes a new node and copies the given data into memory. The head
 * pointer is set if the linked list is empty, otherwise the node is added to
 * the end of the linked list with the tail pointer set to the new node.
 *
 * @param llist Pointer to the linked list structure.
 * @param data Pointer to the data to be loaded into the node.
 *
 * @returns void
 *
 * @b Example
 * @snippet linked_list.test.c Appending nodes
 */

/**
 * @fn void llist_prepend(llist_t *llist, void *data)
 *
 * @brief Adds a node to the start of the linked list.
 *
 * Initializes a new node and copies the given data into memory. The head
 * pointer is set if the linked list is empty, otherwise the new node is
 * prepended to the current head of the list. The previous head is now the
 * second node in the linked list.
 *
 * @param llist Pointer to the linked list structure.
 * @param data Pointer to the data to be loaded into the node.
 *
 * @returns void
 *
 * @b Example
 * @snippet linked_list.test.c Prepending nodes
 */

/**
 * @fn void llist_insert(llist_t *llist, void *data, size_t idx)
 *
 * Initializes a new node and copies the given data into memory. The node is
 * inserted at the position given by `idx`, with the new node preceding the node
 * at position `idx`.
 *
 * @param llist Pointer to the linked list structure.
 * @param data Pointer to the data to be loaded into the node.
 * @param size_t Integer that corresponds to the destination position.
 *
 * @returns void
 *
 * @b Example
 * @snippet linked_list.test.c Inserting nodes
 */

/**
 * @fn void llist_move(llist_t *llist, lnode_t *node, lnode_t *dst, lnode_t
 * *dst_ptr)
 *
 * @brief Moves a node in the linked list to the given destination.
 *
 * Moves a node in the linked list to the given destination node's `next`
 * or `prev` pointer. The `dst_ptr` is checked to ensure it belongs to the node
 * given by `dst`.
 *
 * @param llist Pointer to the linked list structure.
 * @param node Node to be moved.
 * @param dst Destination to move the given node.
 * @param dst_ptr Destination node's `next` or `prev` pointer.
 *
 * @returns void
 *
 * @b Example
 * @snippet linked_list.test.c Moving nodes
 */

/**
 * @fn void llist_swap(llist_t *llist, lnode_t *a, lnode_t *b)
 *
 * @brief Swaps two nodes in a linked list.
 *
 * Swaps two nodes, `a` and `b` in the given `llist_t`, by changing
 * `a->prev->next` from `a` to `b` (the next pointer of the node preceding `a`).
 * The node proceeding `a` has its `prev` pointer changed to point to `b`
 * (`a->next->prev`). Similarly, the same is done for node `b`
 * <STRONG>after</STRONG> `a` has been updated. Finally, the `a` node's `prev`
 * pointer is updated to point to `b`, and `next` pointer is set to the `b`
 * node's `next` pointer. The same is <STRONG>then</STRONG> done for `b`.
 *
 * Adjacent nodes are handled in a slightly different manner, with the only
 * difference being the `a` node's previous pointer being set to `b` instead of
 * `b->next`, and the `b` node's next pointer being set to node `a`.
 *
 * @param llist Pointer to the linked list structure.
 * @param a The node to be swapped with node `b`.
 * @param b The node to be swapped with node `a`.
 *
 * @returns void
 *
 * @remarks The order of operations for swapping adjacent nodes is important. If
 * `a` does <STRONG>not</STRONG> precede `b`, then the function is called again
 * with the nodes swapped in the function's arguments.
 *
 * @b Example
 * @snippet linked_list.test.c Swapping nodes
 */

/**
 * @fn void llist_delete(llist_t *llist, const void *key)
 *
 * @brief Deletes a node in a linked list.
 *
 * Deletes a node in a linked list after connecting the nodes `prev` and `next`
 * nodes together, and freeing the resources associated to it.
 *
 * @param llist Pointer to the linked list structure.
 * @param key Pointer to the node to be deleted.
 *
 * @returns void
 *
 * @b Example
 * @snippet linked_list.test.c Deleting nodes
 */

/**
 * @fn void llist_erase(llist_t *llist, lnode_t *start, lnode_t *end)
 *
 * @brief Erases a range of nodes in a linked list.
 *
 * Removes nodes starting from @p start up to (but not including) @p end.
 *
 * @param llist Pointer to the linked list structure.
 * @param start First node to erase (inclusive).
 * @param end Node marking the end of the range (not erased).
 *
 * @returns void
 *
 * @b Example
 * @snippet linked_list.test.c Example
 */

/**
 * @fn void llist_clear(llist_t *llist)
 *
 * @brief Clears all nodes from a linked list.
 *
 * Deletes all nodes in the list and frees their associated data.
 *
 * @param llist Pointer to the linked list structure.
 *
 * @returns void
 *
 * @remarks After this call, @p llist will be empty.
 *
 * @b Example
 * @snippet linked_list.test.c Clearing lists
 */

/**
 * @fn void llist_copy(llist_t *dst, llist *src)
 *
 * @brief Copies data from one linked list to another.
 *
 * Copies data from the @p src linked list to the @p dst linked list, starting
 * from the @p src `head` node, and ending at the `tail` node.
 *
 * @param dst Pointer to the desination linked list structure.
 * @param src Pointer to the source linked list structure.
 *
 * @returns void
 *
 * @remarks The @p dst linked list will be cleared if it is not empty.
 *
 * @b Example
 * @snippet linked_list.test.c Copying lists
 */

/**
 * @fn void llist_reverse(llist_t *llist)
 *
 * @brief Reverses nodes in a linked list.
 *
 * Swaps the `prev` and `next pointers for all nodes in a linked list, and
 * finally swaps the `head` and `tail` pointers.
 *
 * @param llist Pointer to the linked list structure.
 *
 * @returns void
 *
 * @b Example
 * @snippet linked_list.test.c Reversing nodes
 */

/**
 * @fn size_t llist_index(llist_t *llist, lnode_t *node)
 *
 * @brief Returns the index of a node in a linked list.
 *
 * Performs a linear search in a linked list to find the node that equals @p
 * node.
 *
 * @param llist Pointer to the linked list structure.
 *
 * @returns The index of the node that equals @p node.
 *
 * @remarks The `head` node would have an index of `0`.
 *
 * @b Example
 * @snippet linked_list.test.c Index of a node
 */

/**
 * @fn lnode_t *llist_find(llist_t *llist, const void *key)
 *
 * @brief Finds a node in a linked list that contains the @p key value that has
 * the same size as `data_size`.
 *
 * Performs a linear search over a linked list, and performs a `memcmp` for each
 * node to check if it contains the data of @p key.
 *
 * @param llist Pointer to the linked list structure.
 * @param key The data to search for in each node's `data` field.
 *
 * @returns The node containing the data that matches @p key, or `NULL` if not
 * found.
 *
 * @b Example
 * @snippet linked_list.test.c Finding nodes
 */

/**
 * @fn void lnode_t *llist_lsearch(llist_t *llist, const void *key)
 *
 * @brief Performs a linear search over a linked list to find the given @p key.
 *
 * Performs a linear search over a linked list, and performs a `memcmp` for each
 * node to check if it contains the data of @p key.
 *
 * @param llist Pointer to the linked list structure.
 * @param key The data to search for in each node's `data` field.
 *
 * @returns The node containing the data that matches @p key, or `NULL` if not
 * found.
 *
 * @b Example
 * @snippet linked_list.test.c Linear search
 *
 * @see https://en.wikipedia.org/wiki/Linear_search
 */

/**
 * @fn void llist_bsort(llist_t *llist)
 *
 * @brief Sorts an array using the bubblesort algorithm.
 *
 * Sorts a vector using the bubble sort algorithm. It is not recommended to use
 * this algorithm over the others available. However, it remains in the library
 * for demonstration purposes. Use of this function requires the comparator
 * function pointer to be set.
 *
 * @param llist Pointer to the linked list structure.
 *
 * @returns void
 *
 * @b Example
 * @snippet linked_list.test.c Bubble sort
 *
 * @see https://en.wikipedia.org/wiki/Bubble_sort
 */

/**
 * @fn void llist_qsort(llist_t *llist, lnode_t *lo, lnode_t *hi)
 *
 * @brief Sorts an array using the quicksort algorithm.
 *
 * Sorts a vector using the quicksort algorithm. This quicksort algorithm makes
 * use of the Lomuto partition scheme.
 *
 * @param llist Pointer to the linked list structure.
 * @param lo The first node in the linked list.
 * @param hi The last node in the linked list.
 *
 * @returns void
 *
 * @b Example
 * @snippet linked_list.test.c Quicksort
 *
 * @remarks The @p lo parameter should be the `head` of the linked list, and the
 * @p hi parameter should be the `tail` of the linked list.
 *
 * @see https://en.wikipedia.org/wiki/Quicksort
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "defs.h"
#include <stdbool.h>

#ifdef __clang__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct llnode
{
    void          *data;
    struct llnode *prev;
    struct llnode *next;

} llnode_t;

typedef struct llist
{
    size_t    data_size;

    llnode_t *head;
    llnode_t *tail;

    int (*_cmp)(const void *, const void *);

} llist_t;

LIBCSPD_API void   llist_init(llist_t *llist, size_t data_size);
LIBCSPD_API void   llist_append(llist_t *llist, void *data);
LIBCSPD_API void   llist_prepend(llist_t *llist, void *data);
LIBCSPD_API void   llist_insert(llist_t *llist, void *data, size_t idx);
LIBCSPD_API void   llist_move(llist_t *llist, llnode_t *node, llnode_t *dst,
                              llnode_t *dst_ptr);
LIBCSPD_API void   llist_swap(llist_t *llist, llnode_t *a, llnode_t *b);
LIBCSPD_API void   llist_delete(llist_t *llist, const void *keyt);
LIBCSPD_API void   llist_erase(llist_t *llist, llnode_t *start, llnode_t *end);
LIBCSPD_API void   llist_clear(llist_t *llist);
LIBCSPD_API void   llist_copy(llist_t *dst, llist_t *src);
LIBCSPD_API void   llist_reverse(llist_t *llist);
LIBCSPD_API size_t llist_index(llist_t *llist, llnode_t *node);
LIBCSPD_API llnode_t *llist_find(llist_t *llist, const void *key);
LIBCSPD_API llnode_t *llist_lsearch(llist_t *llist, const void *key);
LIBCSPD_API void      llist_bsort(llist_t *llist);
LIBCSPD_API void      llist_qsort(llist_t *llist, llnode_t *lo, llnode_t *hi);

#define print_llist(type, llist, reverse)                                      \
    {                                                                          \
        printf("{ ");                                                          \
        llnode_t *_curr = !reverse ? (llist)->head : (llist)->tail;            \
                                                                               \
        while (_curr != NULL) {                                                \
            print(*(type *)_curr->data, " ");                                  \
            _curr = !reverse ? _curr->next : _curr->prev;                      \
        }                                                                      \
        printf("} \n");                                                        \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LINKED_LIST_H
