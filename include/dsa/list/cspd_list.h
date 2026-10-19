/**
 * @file cspd_list.h
 * @brief Linked list data structures and algorithms.
 *
 * @see https://en.wikipedia.org/wiki/Linked_list
 */

#ifndef CSPD_LIST_H
#define CSPD_LIST_H

#include "cspd_exports.h"
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
 * @var cspd_lnode::data
 * Memory which has been allocated for the linked list node to store data.
 *
 * @var cspd_lnode::prev
 * Pointer to the previous node in the linked list.
 *
 * @var cspd_lnode::next
 * Pointer to the next node in the linked list.
 */
typedef struct cspd_lnode_t
{
    void                *data;
    struct cspd_lnode_t *prev;
    struct cspd_lnode_t *next;

} cspd_lnode;

/**
 * @brief Data structure for linked list.
 *
 * @var cspd_list::data_size
 * The size of the data in bytes being stored in the linked list nodes.
 *
 * @var cspd_list::head
 * Pointer to the first node in the linked list.
 *
 * @var cspd_list::tail
 * Pointer to the last node in the linked list.
 */
typedef struct cspd_list_t
{
    usize       data_size;
    cspd_lnode *head;
    cspd_lnode *tail;

} cspd_list;

/**
 * @brief Initializes a new linked list.
 *
 * Sets `data_size` to the given parameter, and sets the `head` and `tail`
 * pointers to `NULL`.
 *
 * @param list Pointer to the linked list to be initialized.
 * @param data_size The size of the data type in bytes.
 *
 * @b Example
 * @snippet cspd_list.test.c Initialize linked list
 */
CSPD_API void cspd_list_init(cspd_list *list, usize data_size);

/**
 * @brief Adds a node to the end of the linked list.
 *
 * Initializes a new node and copies the given data into memory. The head
 * pointer is set if the linked list is empty, otherwise the node is added to
 * the end of the linked list with the tail pointer set to the new node.
 *
 * @param list Pointer to the linked list structure.
 * @param data Pointer to the data to be loaded into the node.
 *
 * @b Example
 * @snippet cspd_list.test.c Appending nodes
 */
CSPD_API void cspd_list_append(cspd_list *list, void *data);

/**
 * @brief Adds a node to the start of the linked list.
 *
 * Initializes a new node and copies the given data into memory. The head
 * pointer is set if the linked list is empty, otherwise the new node is
 * prepended to the current head of the list. The previous head is now the
 * second node in the linked list.
 *
 * @param list Pointer to the linked list structure.
 * @param data Pointer to the data to be loaded into the node.
 *
 * @b Example
 * @snippet cspd_list.test.c Prepending nodes
 */
CSPD_API void cspd_list_prepend(cspd_list *list, void *data);

/**
 * @brief Prepends a new node before the node at the given index.
 *
 * Initializes a new node and copies the given data into memory. The node is
 * inserted at the position given by `idx`, with the new node preceding the node
 * at position `idx`.
 *
 * @param list Pointer to the linked list structure.
 * @param data Pointer to the data to be loaded into the node.
 * @param usize Integer that corresponds to the destination position.
 *
 * @b Example
 * @snippet cspd_list.test.c Inserting nodes
 */
CSPD_API void cspd_list_insert(cspd_list *list, void *data, usize idx);

/**
 * @brief Moves a node in the linked list to the given destination.
 *
 * Moves a node in the linked list to the given destination node's `next`
 * or `prev` pointer. The `dst_ptr` is checked to ensure it belongs to the node
 * given by `dst`.
 *
 * @param list Pointer to the linked list structure.
 * @param node Node to be moved.
 * @param dst Destination to move the given node.
 * @param dst_ptr Destination node's `next` or `prev` pointer.
 *
 * @b Example
 * @snippet cspd_list.test.c Moving nodes
 */
CSPD_API void cspd_list_move(cspd_list *list, cspd_lnode *node, cspd_lnode *dst,
                             cspd_lnode *dst_ptr);

/**
 * @brief Swaps two nodes in a linked list.
 *
 * Swaps two nodes, `a` and `b` in the given `cspd_list`, by changing
 * `a->prev->next`from `a` to `b` (the next pointer of the node preceding `a`).
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
 * @param list Pointer to the linked list structure.
 * @param a The node to be swapped with node `b`.
 * @param b The node to be swapped with node `a`.
 *
 * @remarks The order of operations for swapping adjacent nodes is important. If
 * `a` does <STRONG>not</STRONG> precede `b`, then the function is called again
 * with the nodes swapped in the function's arguments.
 *
 * @b Example
 * @snippet cspd_list.test.c Swapping nodes
 */
CSPD_API void cspd_list_swap(cspd_list *list, cspd_lnode *a, cspd_lnode *b);

/**
 * @brief Deletes a node in a linked list.
 *
 * Deletes a node in a linked list after connecting the nodes `prev` and `next`
 * nodes together, and freeing the resources associated to it.
 *
 * @param list Pointer to the linked list structure.
 * @param key Pointer to the node to be deleted.
 *
 * @b Example
 * @snippet cspd_list.test.c Deleting nodes
 */
CSPD_API void cspd_list_delete(cspd_list *list, const void *keyt);

/**
 * @brief Erases a range of nodes in a linked list.
 *
 * Removes nodes starting from @p start up to (but not including) @p end.
 *
 * @param list Pointer to the linked list structure.
 * @param start First node to erase (inclusive).
 * @param end Node marking the end of the range (not erased).
 *
 * @b Example
 * @snippet cspd_list.test.c Example
 */
CSPD_API void cspd_list_erase(cspd_list *list, cspd_lnode *start,
                              cspd_lnode *end);

/**
 * @brief Clears all nodes from a linked list.
 *
 * Deletes all nodes in the list and frees their associated data.
 *
 * @param list Pointer to the linked list structure.
 *
 * @remarks After this call, @p list will be empty.
 *
 * @b Example
 * @snippet cspd_list.test.c Clearing lists
 */
CSPD_API void cspd_list_clear(cspd_list *list);

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
 * @snippet cspd_list.test.c Copying lists
 */
CSPD_API void cspd_list_copy(cspd_list *dst, cspd_list *src);

/**
 * @brief Reverses nodes in a linked list.
 *
 * Swaps the `prev` and `next pointers for all nodes in a linked list, and
 * finally swaps the `head` and `tail` pointers.
 *
 * @param list Pointer to the linked list structure.
 *
 * @b Example
 * @snippet cspd_list.test.c Reversing nodes
 */
CSPD_API void cspd_list_reverse(cspd_list *list);

/**
 * @brief Returns the index of a node in a linked list.
 *
 * Performs a linear search in a linked list to find the node that equals @p
 * node.
 *
 * @param list Pointer to the linked list structure.
 *
 * @returns The index of the node that equals @p node.
 *
 * @remarks The `head` node would have an index of `0`.
 *
 * @b Example
 * @snippet cspd_list.test.c Index of a node
 */
CSPD_API usize cspd_list_index(cspd_list *list, cspd_lnode *node);

/**
 * @brief Finds a node in a linked list that contains the @p key value that has
 * the same size as `data_size`.
 *
 * Performs a linear search over a linked list, and performs a `memcmp` for each
 * node to check if it contains the data of @p key.
 *
 * @param list Pointer to the linked list structure.
 * @param key The data to search for in each node's `data` field.
 *
 * @returns The node containing the data that matches @p key, or `NULL` if not
 * found.
 *
 * @b Example
 * @snippet cspd_list.test.c Finding nodes
 */
CSPD_API cspd_lnode *cspd_list_find(cspd_list *list, const void *key);

/**
 * @brief Performs a linear search over a linked list to find the given @p key.
 *
 * Performs a linear search over a linked list, and performs a `memcmp` for each
 * node to check if it contains the data of @p key.
 *
 * @param list Pointer to the linked list structure.
 * @param key The data to search for in each node's `data` field.
 *
 * @returns The node containing the data that matches @p key, or `NULL` if not
 * found.
 *
 * @b Example
 * @snippet cspd_list.test.c Linear search
 *
 * @see https://en.wikipedia.org/wiki/Linear_search
 */
CSPD_API cspd_lnode *cspd_list_lsearch(cspd_list *list, const void *key);

/**
 * @brief Sorts an array using the bubblesort algorithm.
 *
 * Sorts a linked list the bubble sort algorithm. It is not recommended to use
 * this algorithm over the others available. However, it remains in the library
 * for demonstration purposes. Use of this function requires the comparator
 * function pointer to be set.
 *
 * @param list Pointer to the linked list structure.
 * @param cmp Comparatorfunction pointer.
 *
 * @b Example
 * @snippet cspd_list.test.c Bubble sort
 *
 * @see https://en.wikipedia.org/wiki/Bubble_sort
 */
CSPD_API void cspd_list_bsort(cspd_list *list, cspd_cmp cmp);

/**
 * @brief Sorts an array using the quicksort algorithm.
 *
 * Sorts a linked list using the quicksort algorithm. This quicksort algorithm
 * makes use of the Lomuto partition scheme.
 *
 * @param list Pointer to the linked list structure.
 * @param lo Pointer to the first node in the linked list.
 * @param hi Pointer to the last node in the linked list.
 * @param cmp Comparator function pointer.
 *
 * @b Example
 * @snippet cspd_list.test.c Quicksort
 *
 * @remarks The @p lo parameter should be the `head` of the linked list, and the
 * @p hi parameter should be the `tail` of the linked list.
 *
 * @see https://en.wikipedia.org/wiki/Quicksort
 */
CSPD_API void cspd_list_qsort(cspd_list *list, cspd_lnode *lo, cspd_lnode *hi,
                              cspd_cmp cmp);

/**
 * @brief Prints the contents of the linked list.
 *
 * Basic print function for primtive types that casts each element to the
 * specified type and prints them to standard output. The linked list can be
 * printed in reverse if instructed.
 *
 * @param TYPE Type of data to be casted.
 * @param LIST The linked list to be printed out.
 * @param REVERSE Boolean to control order of printing.
 */
#define cspd_print_list(TYPE, LIST, REVERSE)                                   \
    {                                                                          \
        printf("{ ");                                                          \
        cspd_lnode *_curr = !REVERSE ? (LIST)->head : (LIST)->tail;            \
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
 * Generates a typedef for a `NAME_list` and `NAME_lnode` type, and the
 * functions defined in this header file.
 *
 * @param NAME  The name prefix used for the generated type and functions.
 * @param TYPE  The element type whose size is used to initialize the linked
 * list.
 *
 * @note This macro must be invoked at file scope, not inside a function.
 *
 * @par Example
 * @code
 *   cspd_list_declare(i32, i32)
 *
 *   i32_list l;
 *   i32_list_init(&l);
 * @endcode
 */
#define cspd_list_declare(NAME, TYPE)                                          \
                                                                               \
    typedef cspd_list  NAME##_list;                                            \
    typedef cspd_lnode NAME##_lnode;                                           \
                                                                               \
    static inline void NAME##_cspd_list_init(NAME##_list *list)                \
    {                                                                          \
        cspd_list_init(list, sizeof(TYPE));                                    \
    }                                                                          \
                                                                               \
    static inline void NAME##_cspd_list_append(NAME##_list *list, TYPE *data)  \
    {                                                                          \
        cspd_list_append(list, (void *)data);                                  \
    }                                                                          \
                                                                               \
    static inline void NAME##_cspd_list_prepend(NAME##_list *list, TYPE *data) \
    {                                                                          \
        cspd_list_prepend(list, (void *)data);                                 \
    }                                                                          \
                                                                               \
    static inline void NAME##_cspd_list_insert(NAME##_list *list, TYPE *data,  \
                                               usize idx)                      \
    {                                                                          \
        cspd_list_insert(list, (void *)data, idx);                             \
    }                                                                          \
                                                                               \
    static inline void NAME##_cspd_list_move(                                  \
        NAME##_list *list, NAME##_lnode *node, NAME##_lnode *dst,              \
        NAME##_lnode *dst_ptr)                                                 \
    {                                                                          \
        cspd_list_move(list, node, dst, dst_ptr);                              \
    }                                                                          \
                                                                               \
    static inline void NAME##_cspd_list_delete(NAME##_list *list,              \
                                               const TYPE  *key)               \
    {                                                                          \
        cspd_list_delete(list, (const void *)key);                             \
    }                                                                          \
                                                                               \
    static inline void NAME##_cspd_list_erase(                                 \
        NAME##_list *list, NAME##_lnode *start, NAME##_lnode *end)             \
    {                                                                          \
        cspd_list_erase(list, start, end);                                     \
    }                                                                          \
                                                                               \
    static inline void NAME##_cspd_list_clear(NAME##_list *list)               \
    {                                                                          \
        cspd_list_clear(list);                                                 \
    }                                                                          \
                                                                               \
    static inline void NAME##_cspd_list_copy(NAME##_list *dst,                 \
                                             NAME##_list *src)                 \
    {                                                                          \
        cspd_list_copy(dst, src);                                              \
    }                                                                          \
                                                                               \
    static inline void NAME##_cspd_list_reverse(NAME##_list *list)             \
    {                                                                          \
        cspd_list_reverse(list);                                               \
    }                                                                          \
                                                                               \
    static inline usize NAME##_cspd_list_index(NAME##_list  *list,             \
                                               NAME##_lnode *node)             \
    {                                                                          \
        return cspd_list_index(list, node);                                    \
    }                                                                          \
                                                                               \
    static inline NAME##_lnode *NAME##_cspd_list_find(NAME##_list *list,       \
                                                      const TYPE  *key)        \
    {                                                                          \
        return cspd_list_find(list, (const void *)key);                        \
    }                                                                          \
                                                                               \
    static inline NAME##_lnode *NAME##_cspd_list_lsearch(NAME##_list *list,    \
                                                         const TYPE  *key)     \
    {                                                                          \
        return cspd_list_lsearch(list, (const void *)key);                     \
    }                                                                          \
                                                                               \
    static inline void NAME##_cspd_list_bsort(NAME##_list *list, cspd_cmp cmp) \
    {                                                                          \
        cspd_list_bsort(list, cmp);                                            \
    }                                                                          \
                                                                               \
    static inline void NAME##_cspd_list_qsort(                                 \
        NAME##_list *list, NAME##_lnode *lo, NAME##_lnode *hi, cspd_cmp cmp)   \
    {                                                                          \
        cspd_list_qsort(list, lo, hi, cmp);                                    \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_LIST_H
