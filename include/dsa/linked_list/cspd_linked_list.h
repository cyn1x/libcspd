/**
 * @file cspd_linked_list.h
 */

#ifndef CSPD_LINKED_LIST_H
#define CSPD_LINKED_LIST_H

#include "cspd_defs.h"
#include "cspd_types.h"

#ifdef __clang__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Data structure for linked list nodes.
 *
 * @var cspd_llnode::data
 * Memory which has been allocated for the linked list node to store data.
 *
 * @var cspd_llnode::prev
 * Pointer to the previous node in the linked list.
 *
 * @var cspd_llnode::next
 * Pointer to the next node in the linked list.
 */
typedef struct cspd_llnode_t
{
    void                 *data;
    struct cspd_llnode_t *prev;
    struct cspd_llnode_t *next;

} cspd_llnode;

/**
 * @brief Data structure for linked list.
 *
 * @var cspd_llist::data_size
 * The size of the data in bytes being stored in the linked list nodes.
 *
 * @var cspd_llist::head
 * Pointer to the first node in the linked list.
 *
 * @var cspd_llist::tail
 * Pointer to the last node in the linked list.
 */
typedef struct cspd_llist_t
{
    usize        data_size;
    cspd_llnode *head;
    cspd_llnode *tail;

} cspd_llist;

/**
 * @brief Initializes a new linked list.
 *
 * Sets `data_size` to the given parameter, and sets the `head` and `tail`
 * pointers to `NULL`.
 *
 * @param llist Pointer to the linked list to be initialized.
 * @param data_size The size of the data type in bytes.
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Initialize
 */
CSPD_API void cspd_llist_init(cspd_llist *llist, usize data_size);

/**
 * @brief Adds a node to the end of the linked list.
 *
 * Initializes a new node and copies the given data into memory. The head
 * pointer is set if the linked list is empty, otherwise the node is added to
 * the end of the linked list with the tail pointer set to the new node.
 *
 * @param llist Pointer to the linked list structure.
 * @param data Pointer to the data to be loaded into the node.
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Appending nodes
 */
CSPD_API void cspd_llist_append(cspd_llist *llist, void *data);

/**
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
 * @b Example
 * @snippet cspd_linked_list.test.c Prepending nodes
 */
CSPD_API void cspd_llist_prepend(cspd_llist *llist, void *data);

/**
 * @brief Prepends a new node before the node at the given index.
 *
 * Initializes a new node and copies the given data into memory. The node is
 * inserted at the position given by `idx`, with the new node preceding the node
 * at position `idx`.
 *
 * @param llist Pointer to the linked list structure.
 * @param data Pointer to the data to be loaded into the node.
 * @param usize Integer that corresponds to the destination position.
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Inserting nodes
 */
CSPD_API void cspd_llist_insert(cspd_llist *llist, void *data, usize idx);

/**
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
 * @b Example
 * @snippet cspd_linked_list.test.c Moving nodes
 */
CSPD_API void cspd_llist_move(cspd_llist *llist, cspd_llnode *node,
                              cspd_llnode *dst, cspd_llnode *dst_ptr);

/**
 * @brief Swaps two nodes in a linked list.
 *
 * Swaps two nodes, `a` and `b` in the given `cspd_llist`, by changing
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
 * @remarks The order of operations for swapping adjacent nodes is important. If
 * `a` does <STRONG>not</STRONG> precede `b`, then the function is called again
 * with the nodes swapped in the function's arguments.
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Swapping nodes
 */
CSPD_API void cspd_llist_swap(cspd_llist *llist, cspd_llnode *a,
                              cspd_llnode *b);

/**
 * @brief Deletes a node in a linked list.
 *
 * Deletes a node in a linked list after connecting the nodes `prev` and `next`
 * nodes together, and freeing the resources associated to it.
 *
 * @param llist Pointer to the linked list structure.
 * @param key Pointer to the node to be deleted.
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Deleting nodes
 */
CSPD_API void cspd_llist_delete(cspd_llist *llist, const void *keyt);

/**
 * @brief Erases a range of nodes in a linked list.
 *
 * Removes nodes starting from @p start up to (but not including) @p end.
 *
 * @param llist Pointer to the linked list structure.
 * @param start First node to erase (inclusive).
 * @param end Node marking the end of the range (not erased).
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Example
 */
CSPD_API void cspd_llist_erase(cspd_llist *llist, cspd_llnode *start,
                               cspd_llnode *end);

/**
 * @brief Clears all nodes from a linked list.
 *
 * Deletes all nodes in the list and frees their associated data.
 *
 * @param llist Pointer to the linked list structure.
 *
 * @remarks After this call, @p llist will be empty.
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Clearing lists
 */
CSPD_API void cspd_llist_clear(cspd_llist *llist);

/**
 * @brief Copies data from one linked list to another.
 *
 * Copies data from the @p src linked list to the @p dst linked list, starting
 * from the @p src `head` node, and ending at the `tail` node.
 *
 * @param dst Pointer to the desination linked list structure.
 * @param src Pointer to the source linked list structure.
 *
 * @remarks The @p dst linked list will be cleared if it is not empty.
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Copying lists
 */
CSPD_API void cspd_llist_copy(cspd_llist *dst, cspd_llist *src);

/**
 * @brief Reverses nodes in a linked list.
 *
 * Swaps the `prev` and `next pointers for all nodes in a linked list, and
 * finally swaps the `head` and `tail` pointers.
 *
 * @param llist Pointer to the linked list structure.
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Reversing nodes
 */
CSPD_API void cspd_llist_reverse(cspd_llist *llist);

/**
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
 * @snippet cspd_linked_list.test.c Index of a node
 */
CSPD_API usize cspd_llist_index(cspd_llist *llist, cspd_llnode *node);

/**
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
 * @snippet cspd_linked_list.test.c Finding nodes
 */
CSPD_API cspd_llnode *cspd_llist_find(cspd_llist *llist, const void *key);

/**
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
 * @snippet cspd_linked_list.test.c Linear search
 *
 * @see https://en.wikipedia.org/wiki/Linear_search
 */
CSPD_API cspd_llnode *cspd_llist_lsearch(cspd_llist *llist, const void *key);

/**
 * @brief Sorts an array using the bubblesort algorithm.
 *
 * Sorts a linked list the bubble sort algorithm. It is not recommended to use
 * this algorithm over the others available. However, it remains in the library
 * for demonstration purposes. Use of this function requires the comparator
 * function pointer to be set.
 *
 * @param llist Pointer to the linked list structure.
 * @param cmp Comparator function pointer.
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Bubble sort
 *
 * @see https://en.wikipedia.org/wiki/Bubble_sort
 */
CSPD_API void cspd_llist_bsort(cspd_llist *llist, cspd_cmp cmp);

/**
 * @brief Sorts an array using the quicksort algorithm.
 *
 * Sorts a linked list using the quicksort algorithm. This quicksort algorithm
 * makes use of the Lomuto partition scheme.
 *
 * @param llist Pointer to the linked list structure.
 * @param lo Pointer to the first node in the linked list.
 * @param hi Pointer to the last node in the linked list.
 * @param cmp Comparator function pointer.
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Quicksort
 *
 * @remarks The @p lo parameter should be the `head` of the linked list, and the
 * @p hi parameter should be the `tail` of the linked list.
 *
 * @see https://en.wikipedia.org/wiki/Quicksort
 */
CSPD_API void cspd_llist_qsort(cspd_llist *llist, cspd_llnode *lo,
                               cspd_llnode *hi, cspd_cmp cmp);

/**
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
#define cspd_print_llist(TYPE, LIST, REVERSE)                                  \
    {                                                                          \
        printf("{ ");                                                          \
        cspd_llnode *_curr = !REVERSE ? (LIST)->head : (LIST)->tail;           \
                                                                               \
        while (_curr != NULL) {                                                \
            cspd_print(*(TYPE *)_curr->data, " ");                             \
            _curr = !REVERSE ? _curr->next : _curr->prev;                      \
        }                                                                      \
        printf("} \n");                                                        \
    }

/**
 * @brief Declares a typed linked list and its associated functions for a given
 * type.
 *
 * Generates a typedef for a `NAME_llist` type and the following function
 * declarations:
 * -
 *
 * @param NAME  The name prefix used for the generated type and functions.
 * @param TYPE  The element type whose size is used to initialize the linked
 * list.
 *
 * @note This macro must be invoked at file scope, not inside a function.
 *
 * @par Example:
 * @code
 *   cspd_llist_declare(i32, i32);
 *
 *   i32_llist l;
 *   i32_llist_init(&l);
 * @endcode
 */
#define cspd_llist_declare(NAME, TYPE)                                         \
                                                                               \
    typedef cspd_llist NAME##_llist;                                           \
                                                                               \
    static inline void NAME##_llist_init(NAME##_llist *llist)                  \
    {                                                                          \
        cspd_llist_init(llist, sizeof(TYPE));                                  \
    }                                                                          \
                                                                               \
    // TODO: 0027 - Generic type definitions

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_LINKED_LIST_H
