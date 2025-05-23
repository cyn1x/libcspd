/**
 * @file bstree.h
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "defs.h"

#ifdef __clang__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct bstnode
{
    void           *data;
    struct bstnode *left;
    struct bstnode *right;
} bstnode_t;

typedef struct bstree
{
    bstnode_t *root;
    size_t     data_size;

    int (*_cmp)(const void *, const void *);
} bstree_t;

LIBCSPD_API void       bstree_init(bstree_t *bstree, size_t data_size);
LIBCSPD_API bstnode_t *bstree_add(bstree_t *bstree, void *data);
LIBCSPD_API void       bstree_clear(bstree_t *bstree);

#define print_binary_search_tree(type, vec)                                    \
    {                                                                          \
        printf("{ ");                                                          \
        for (size_t i = 0; i < (vec)->size; ++i) {                             \
            bstnode_t *_node = *(bstnode_t **)vector_get(vec, i);              \
            print((*(type *)_node->data), " ");                                \
        }                                                                      \
        printf("} \n");                                                        \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BINARY_SEARCH_TREE_H
