/**
 * @file binary_tree.h
 */

/**
 * @typedef struct cspd_btnode
 *
 * @brief Data structure for nodes residing in a binary tree.
 *
 * @var cspd_btnode::data
 * Memory which has been allocated for the binary tree node to store data.
 *
 * @var cspd_btnode::left
 * The binary tree node's left pointer.
 *
 * @var cspd_btnode::right
 * The binary tree node's right pointer.
 */

/**
 * @typedef struct cspd_btree
 *
 * @brief Data structure for binary tree.
 *
 * @var cspd_btree::data_size
 * The size of the data in bytes being stored in the nodes that reside in the
 * binary tree.
 *
 * @var cspd_btree::root
 * Pointer to the first node in the binary tree.
 *
 * @var cspd_btree::_cmp
 * Comparator function used for sorting or searching. The library contains some
 * basic types as seen below, which can be assigned to the `_cmp` variable. You
 * can also provide your own comparator functions.
 */

/**
 * @fn void function_name(cspd_btree *btree)
 *
 * @brief .
 *
 *
 *
 * @param btree Pointer to the binary tree structure
 *
 * @returns
 *
 * @b Example
 * @snippet cspd_btree_test.c Example
 */

#ifndef CSPD_BTREE_H
#define CSPD_BTREE_H

#include "cspd_defs.h"
#include "queue.h"
#include "cspd_vector.h"

#ifdef __clang__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct cspd_btnode
{
    void               *data;
    struct cspd_btnode *left;
    struct cspd_btnode *right;

} cspd_btnode;

typedef struct cspd_btree
{
    size_t       data_size;
    cspd_btnode *root;

    int (*_cmp)(const void *, const void *);

} cspd_btree;

LIBCSPD_API void         cspd_btree_init(cspd_btree *btree, size_t data_size);
LIBCSPD_API cspd_btnode *cspd_btree_add(cspd_btree *btree, cspd_btnode **leaf,
                                        void *data);
LIBCSPD_API cspd_btnode *cspd_btree_insert(cspd_btree   *btree,
                                           cspd_btnode **parent, void *data);
LIBCSPD_API void   cspd_btree_preorder(cspd_btnode *node, cspd_vector *vec);
LIBCSPD_API void   cspd_btree_inorder(cspd_btnode *node, cspd_vector *vec);
LIBCSPD_API void   cspd_btree_postorder(cspd_btnode *node, cspd_vector *vec);
LIBCSPD_API void   cspd_btree_dfs(cspd_btnode *node, cspd_vector *vec);
LIBCSPD_API void   cspd_btree_bfs(cspd_btnode *node, cspd_queue *queue);
LIBCSPD_API void   cspd_btree_invert(cspd_btnode *node);
LIBCSPD_API int32  cspd_btree_height(cspd_btnode *node);
LIBCSPD_API size_t cspd_btree_count(cspd_btnode *node);
LIBCSPD_API void   cspd_btree_clear(cspd_btree *btree);

#define cspd_print_btree(type, vec)                                            \
    {                                                                          \
        printf("{ ");                                                          \
        for (size_t i = 0; i < (vec)->size; ++i) {                             \
            cspd_btnode *_node = *(cspd_btnode **)cspd_vector_get(vec, i);     \
            cspd_print((*(type *)_node->data), " ");                           \
        }                                                                      \
        printf("} \n");                                                        \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_BTREE_H
