/**
 * @file binary_tree.h
 */

/**
 * @typedef struct btnode_t
 *
 * @brief Data structure for nodes residing in a binary tree.
 *
 * @var btnode::data
 * Memory which has been allocated for the binary tree node to store data.
 *
 * @var btnode::left
 * The binary tree node's left pointer.
 *
 * @var btnode::right
 * The binary tree node's right pointer.
 */

/**
 * @typedef struct bintree_t
 *
 * @brief Data structure for binary tree.
 *
 * @var bintree::data_size
 * The size of the data in bytes being stored in the nodes that reside in the
 * binary tree.
 *
 * @var bintree::root
 * Pointer to the first node in the binary tree.
 *
 * @var bintree::_cmp
 * Comparator function used for sorting or searching. The library contains some
 * basic types as seen below, which can be assigned to the `_cmp` variable. You
 * can also provide your own comparator functions.
 */

/**
 * @fn void function_name(bintree_t *btree)
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
 * @snippet binary_tree.test.c Example
 */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "defs.h"
#include "queue.h"
#include "vector.h"

#ifdef __clang__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct btnode
{
    void          *data;
    struct btnode *left;
    struct btnode *right;

} btnode_t;

typedef struct bintree
{
    size_t    data_size;
    btnode_t *root;

    int (*_cmp)(const void *, const void *);

} bintree_t;

LIBCSPD_API void      bintree_init(bintree_t *btree, size_t data_size);
LIBCSPD_API btnode_t *bintree_add(bintree_t *btree, btnode_t **leaf,
                                  void *data);
LIBCSPD_API btnode_t *bintree_insert(bintree_t *btree, btnode_t **parent,
                                     void *data);
LIBCSPD_API void      bintree_preorder(btnode_t *node, vector_t *vec);
LIBCSPD_API void      bintree_inorder(btnode_t *node, vector_t *vec);
LIBCSPD_API void      bintree_postorder(btnode_t *node, vector_t *vec);
LIBCSPD_API void      bintree_dfs(btnode_t *node, vector_t *vec);
LIBCSPD_API void      bintree_bfs(btnode_t *node, queue_t *queue);
LIBCSPD_API void      bintree_invert(btnode_t *node);
LIBCSPD_API int32     bintree_height(btnode_t *node);
LIBCSPD_API size_t    bintree_count(btnode_t *node);
LIBCSPD_API void      bintree_clear(bintree_t *btree);

#define print_binary_tree(type, vec)                                           \
    {                                                                          \
        printf("{ ");                                                          \
        for (size_t i = 0; i < (vec)->size; ++i) {                             \
            btnode_t *_node = *(btnode_t **)vector_get(vec, i);                \
            print((*(type *)_node->data), " ");                                \
        }                                                                      \
        printf("} \n");                                                        \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BINARY_TREE_H
