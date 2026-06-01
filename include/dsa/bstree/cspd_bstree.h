/**
 * @file cspd_bstree.h
 */

#ifndef CSPD_BSTREE_H
#define CSPD_BSTREE_H

#include "cspd_defs.h"

#ifdef __clang__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct cspd_bstnode
{
    void           *data;
    struct bstnode *left;
    struct bstnode *right;
} cspd_bstnode;

typedef struct cspd_bstree
{
    cspd_bstnode *root;
    size_t        data_size;

    int (*_cmp)(const void *, const void *);
} cspd_bstree;

CSPD_API void          cspd_bstree_init(cspd_bstree *bstree, size_t data_size);
CSPD_API cspd_bstnode *cspd_bstree_add(cspd_bstree *bstree, void *data);
CSPD_API void          cspd_bstree_clear(cspd_bstree *bstree);

#define cspd_print_bstree(type, vec)                                           \
    {                                                                          \
        printf("{ ");                                                          \
        for (size_t i = 0; i < (vec)->size; ++i) {                             \
            cspd_bstnode *_node = *(cspd_bstnode **)cspd_vector_get(vec, i);   \
            print((*(type *)_node->data), " ");                                \
        }                                                                      \
        printf("} \n");                                                        \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_BSTREE_H
