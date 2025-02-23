/**
 * @file linked_list.h
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

typedef struct llist_node
{
    void              *data;
    struct llist_node *prev;
    struct llist_node *next;

} lnode_t;

typedef struct llist_t
{
    size_t   data_size;

    lnode_t *head;
    lnode_t *tail;

    int (*_cmp)(const void *, const void *);

} llist_t;

LIBCSPD_API void   llist_init(llist_t *llist_t, size_t data_size);
LIBCSPD_API void   llist_append(llist_t *llist_t, void *data);
LIBCSPD_API void   llist_prepend(llist_t *llist_t, void *data);
LIBCSPD_API void   llist_insert(llist_t *llist_t, void *data, size_t idx);
LIBCSPD_API void   llist_move(llist_t *llist_t, lnode_t *node, lnode_t *dst,
                              lnode_t *dst_ptr);
LIBCSPD_API void   llist_swap(llist_t *llist_t, lnode_t *a, lnode_t *b);
LIBCSPD_API void   llist_delete(llist_t *llist_t, const void *key);
LIBCSPD_API void   llist_erase(llist_t *llist_t, lnode_t *start, lnode_t *end);
LIBCSPD_API void   llist_clear(llist_t *llist_t);
LIBCSPD_API void   llist_copy(llist_t *dst, llist_t *src);
LIBCSPD_API void   llist_reverse(llist_t *llist_t);
LIBCSPD_API size_t llist_index(llist_t *llist_t, lnode_t *node);
LIBCSPD_API lnode_t *llist_find(llist_t *llist_t, const void *key);
LIBCSPD_API lnode_t *llist_lsearch(llist_t *llist_t, const void *key);
LIBCSPD_API void     llist_bsort(llist_t *llist_t);
LIBCSPD_API void     llist_qsort(llist_t *llist_t, lnode_t *lo, lnode_t *hi);

#define print_llist(type, llist_t, reverse)                                    \
    {                                                                          \
        printf("{ ");                                                          \
        lnode_t *curr = !reverse ? (llist_t)->head : (llist_t)->tail;          \
                                                                               \
        while (curr != NULL) {                                                 \
            print(*(type *)curr->data, " ");                                   \
            curr = !reverse ? curr->next : curr->prev;                         \
        }                                                                      \
        printf("} \n");                                                        \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LINKED_LIST_H
