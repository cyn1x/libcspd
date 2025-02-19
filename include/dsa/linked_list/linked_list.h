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

typedef struct llist
{
    size_t   data_size;

    lnode_t *head;
    lnode_t *tail;

    int (*_cmp)(const void *, const void *);

} llist;

LIBCSPD_API void     llist_init(llist *llist, size_t data_size);
LIBCSPD_API void     llist_append(llist *llist, void *data);
LIBCSPD_API void     llist_prepend(llist *llist, void *data);
LIBCSPD_API void     llist_insert(llist *llist, void *data, size_t idx);
LIBCSPD_API void     llist_move(llist *llist, lnode_t *node, lnode_t *dst,
                                lnode_t *dst_ptr);
LIBCSPD_API void     llist_swap(llist *llist, lnode_t *a, lnode_t *b);
LIBCSPD_API void     llist_delete(llist *llist, const void *key);
LIBCSPD_API void     llist_erase(llist *llist, lnode_t *start, lnode_t *end);
LIBCSPD_API void     llist_clear(llist *llist);
LIBCSPD_API void     llist_copy(llist *dst, llist *src);
LIBCSPD_API void     llist_reverse(llist *llist);
LIBCSPD_API size_t   llist_index(llist *llist, lnode_t *node);
LIBCSPD_API lnode_t *llist_find(llist *llist, const void *key);
LIBCSPD_API lnode_t *llist_lsearch(llist *llist, const void *key);
LIBCSPD_API void     llist_bsort(llist *llist);
LIBCSPD_API void     llist_qsort(llist *llist, lnode_t *lo, lnode_t *hi);

#define print_llist(type, llist, reverse)                                      \
    {                                                                          \
        printf("{ ");                                                          \
        lnode_t *curr = !reverse ? (llist)->head : (llist)->tail;              \
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
