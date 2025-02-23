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
