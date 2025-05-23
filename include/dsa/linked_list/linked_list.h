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
 * @b Example
 * The provided comparator functions can be defined in a header file.
 * @include defs.test.h
 * Once defined, assign the address of the defined functions from the header
 * file to the comparator function pointer.
 * @snippet linked_list.test.c Comparator function
 */

/**
 * @fn void llist_init(llist_t *llist_t, size_t data_size)
 *
 * @brief Initializes a new linked list.
 *
 * Sets `data_size` to the given parameter, and sets the head and tail pointers
 * to `NULL`.
 *
 * @param vec Pointer to the linked list to be initialized.
 * @param data_size The size of the data type in bytes.
 *
 * @b Example
 * @snippet linked_list.test.c Initialize
 */

/**
 * @fn node *node_init(llist_t *llist_t)
 *
 * @brief Initializes a new node.
 *
 * Memory is allocated for the new node and the data that will reside within the
 * new node structure. The `prev` and `next` pointers are set to `NULL`.
 *
 * @param llist Pointer to the linked list structure
 *
 * @returns Pointer to the new node in memory.
 *
 * @b Example
 * @snippet linked_list.test.c Initialize
 */

/**
 * @fn void llist_append(llist_t *llist_t, void *data)
 *
 * @brief Adds a node to the end of the linked list.
 *
 * Initializes a new node and copies the given data into memory. The head
 * pointer is set if the linked list is empty, otherwise the node is added to
 * the end of the linked list with the tail pointer set to the new node.
 *
 * @param llist Pointer to the linked list structure
 * @param data Pointer to the data to be loaded into the node
 *
 * @b Example
 * @snippet linked_list.test.c Appending nodes
 */

/**
 * @fn void llist_prepend(llist_t *llist_t, void *data)
 *
 * @brief Adds a node to the start of the linked list.
 *
 * Initializes a new node and copies the given data into memory. The head
 * pointer is set if the linked list is empty, otherwise the new node is
 * prepended to the current head of the list. The previous head is now the
 * second node in the linked list.
 *
 * @param llist Pointer to the linked list structure
 * @param data Pointer to the data to be loaded into the node
 *
 * @b Example
 * @snippet linked_list.test.c Prepending nodes
 */

/**
 * @fn void llist_insert(llist_t *llist_t, void *data, size_t idx)
 *
 * Initializes a new node and copies the given data into memory. The node is
 * inserted at the position given by `idx`, with the new node preceding the node
 * at position at idx.
 *
 * @param llist Pointer to the linked list structure
 * @param data Pointer to the data to be loaded into the node
 * @param size_t Integer that corresponds to the destination position
 *
 * @b Example
 * @snippet linked_list.test.c Inserting nodes
 */

/**
 * @fn void llist_move(llist_t *llist_t, lnode_t *node, lnode_t *dst, lnode_t
 * *dst_ptr)
 *
 * @brief Moves a node in the linked list to the given destination.
 *
 * Moves a node in the linked list to the given destination node's `next`
 * or `prev` pointer. The `dst_ptr` is checked to ensure it belongs to the node
 * given by `dst`.
 *
 * @param llist Pointer to the linked list structure
 * @param node Node to be moved
 * @param dst Destination to move the given node
 * @param dst_ptr Destination node's `next` or `prev` pointer
 *
 * @b Example
 * @snippet linked_list.test.c Moving nodes
 */

/**
 * @fn void llist_swap(llist_t *llist_t, lnode_t *a, lnode_t *b)
 *
 * @brief Swaps two nodes in a linked list.
 *
 *
 *
 * @param llist_t Pointer to the linked list structure
 *
 * @returns
 *
 * @b Example
 * @snippet linked_list.test.c Example
 */

/**
 * @fn void llist_delete(llist_t *llist_t, const void *key)
 *
 * @brief .
 *
 *
 *
 * @param llist_t Pointer to the linked list structure
 *
 * @returns
 *
 * @b Example
 * @snippet linked_list.test.c Example
 */

/**
 * @fn void llist_erase(llist_t *llist_t, lnode_t *start, lnode_t *end)
 *
 * @brief .
 *
 *
 *
 * @param llist_t Pointer to the linked list structure
 *
 * @returns
 *
 * @b Example
 * @snippet linked_list.test.c Example
 */

/**
 * @fn void llist_clear(llist_t *llist_t)
 *
 * @brief .
 *
 *
 *
 * @param llist_t Pointer to the linked list structure
 *
 * @returns
 *
 * @b Example
 * @snippet linked_list.test.c Example
 */

/**
 * @fn void llist_copy(llist_t *dst, llist_t *src)
 *
 * @brief .
 *
 *
 *
 * @param llist_t Pointer to the linked list structure
 *
 * @returns
 *
 * @b Example
 * @snippet linked_list.test.c Example
 */

/**
 * @fn void llist_reverse(llist_t *llist_t)
 *
 * @brief .
 *
 *
 *
 * @param llist_t Pointer to the linked list structure
 *
 * @returns
 *
 * @b Example
 * @snippet linked_list.test.c Example
 */

/**
 * @fn size_t llist_index(llist_t *llist_t, lnode_t *node)
 *
 * @brief .
 *
 *
 *
 * @param llist_t Pointer to the linked list structure
 *
 * @returns
 *
 * @b Example
 * @snippet linked_list.test.c Example
 */

/**
 * @fn lnode_t *llist_find(llist_t *llist_t, const void *key)
 *
 * @brief .
 *
 *
 *
 * @param llist_t Pointer to the linked list structure
 *
 * @returns
 *
 * @b Example
 * @snippet linked_list.test.c Example
 */

/**
 * @fn void lnode_t *llist_lsearch(llist_t *llist_t, const void *key)
 *
 * @brief .
 *
 *
 *
 * @param llist_t Pointer to the linked list structure
 *
 * @returns
 *
 * @b Example
 * @snippet linked_list.test.c Example
 */

/**
 * @fn void llist_bsort(llist_t *llist_t)
 *
 * @brief .
 *
 *
 *
 * @param llist_t Pointer to the linked list structure
 *
 * @returns
 *
 * @b Example
 * @snippet linked_list.test.c Example
 */

/**
 * @fn void llist_qsort(llist_t *llist_t, lnode_t *lo, lnode_t *hi)
 *
 * @brief .
 *
 *
 *
 * @param llist_t Pointer to the linked list structure
 *
 * @returns
 *
 * @b Example
 * @snippet linked_list.test.c Example
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
