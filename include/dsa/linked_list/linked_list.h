/**
 * @file linked_list.h
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "defs.h"
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct node
{
    void        *data;
    struct node *prev;
    struct node *next;

} node_t;

typedef struct llist
{
    size_t  data_size;

    node_t *head;
    node_t *tail;

    int (*_cmp)(const void *, const void *);

} llist;

LIBCSPD_API void    llist_init(llist *llist, size_t data_size);
LIBCSPD_API void    llist_append(llist *llist, void *data);
LIBCSPD_API void    llist_prepend(llist *llist, void *data);
LIBCSPD_API void    llist_insert(llist *llist, void *data, size_t idx);
LIBCSPD_API void    llist_move(llist *llist, node_t *node, node_t *dst,
                               node_t *dst_ptr);
LIBCSPD_API void    llist_swap(llist *llist, node_t *a, node_t *b);
LIBCSPD_API void    llist_delete(llist *llist, const void *key);
LIBCSPD_API void    llist_erase(llist *llist, node_t *start, node_t *end);
LIBCSPD_API void    llist_clear(llist *llist);
LIBCSPD_API void    llist_copy(llist *dst, llist *src);
LIBCSPD_API void    llist_reverse(llist *llist);
LIBCSPD_API size_t  llist_index(llist *llist, node_t *node);
LIBCSPD_API node_t *llist_find(llist *llist, const void *key);
LIBCSPD_API node_t *llist_lsearch(llist *llist, const void *key);
LIBCSPD_API void    llist_bsort(llist *llist);
LIBCSPD_API void    llist_qsort(llist *llist, node_t *lo, node_t *hi);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LINKED_LIST_H
