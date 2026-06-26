/**
 * @file cspd_btree.h
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
 */

/**
 * @fn void cspd_btree_init(cspd_btree *btree, usize data_size);
 *
 * @brief
 *
 *
 *
 * @param btree
 * @param data_size
 */

/**
 * @fn cspd_btnode cspd_btree_add(cspd_btree  *btree,  cspd_btnode   **leaf,
 * void *data)
 *
 * @brief
 *
 *
 *
 * @param btree
 * @param data
 */

/**
 * @fn cspd_btnode *cspd_btree_insert(cspd_btree *btree, cspd_btnode **parent,
 * void *data);
 *
 * @brief
 *
 *
 *
 * @param btree
 * @param parent
 */

/**
 * @fn void cspd_btree_preorder(cspd_btnode *node, cspd_vector *vec);
 *
 * @brief
 *
 *
 *
 * @param node
 * @param vec
 */

/**
 * @fn void cspd_btree_inorder(cspd_btnode *node, cspd_vector *vec);
 *
 * @brief
 *
 *
 *
 * @param node
 * @param vec
 */

/**
 * @fn void cspd_btree_postorder(cspd_btnode *node, cspd_vector *vec);
 *
 * @brief
 *
 *
 *
 * @param node
 * @param vec
 */

/**
 * @fn void cspd_btree_dfs(cspd_btnode *node, cspd_vector *vec);
 *
 * @brief
 *
 *
 *
 * @param node
 * @param vec
 */

/**
 * @fn void cspd_btree_bfs(cspd_btnode *node, cspd_queue *queue);
 *
 * @brief
 *
 *
 *
 * @param node
 * @param vec
 */

/**
 * @fn void cspd_btree_invert(cspd_btnode *node);
 *
 * @brief
 *
 *
 *
 * @param node
 */

/**
 * @fn int32 cspd_btree_height(cspd_btnode *node);
 *
 * @brief
 *
 *
 *
 * @param node
 */

/**
 * @fn usize cspd_btree_count(cspd_btnode *node);
 *
 * @brief
 *
 *
 *
 * @param node
 */

/**
 * @fn void cspd_btree_clear(cspd_btree *btree);
 *
 * @brief
 *
 *
 *
 * @param btree
 */

/**
 * @def cspd_print_btree(type, vec)
 *
 * @brief Prints the contents of the binary tree.
 *
 *
 *
 * @param type Type of data to be casted.
 * @param vec
 */

#ifndef CSPD_BTREE_H
#define CSPD_BTREE_H

#include "cspd_defs.h"
#include "cspd_queue.h"
#include "cspd_vector.h"

#ifdef __clang__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct cspd_btnode_t
{
    void                 *data;
    struct cspd_btnode_t *left;
    struct cspd_btnode_t *right;

} cspd_btnode;

typedef struct cspd_btree_t
{
    usize        data_size;
    cspd_btnode *root;

} cspd_btree;

CSPD_API void         cspd_btree_init(cspd_btree *btree, usize data_size);
CSPD_API cspd_btnode *cspd_btree_add(cspd_btree *btree, cspd_btnode **leaf,
                                     void *data);
CSPD_API cspd_btnode *cspd_btree_insert(cspd_btree *btree, cspd_btnode **parent,
                                        void *data);
CSPD_API void         cspd_btree_preorder(cspd_btnode *node, cspd_vector *vec);
CSPD_API void         cspd_btree_inorder(cspd_btnode *node, cspd_vector *vec);
CSPD_API void         cspd_btree_postorder(cspd_btnode *node, cspd_vector *vec);
CSPD_API void         cspd_btree_dfs(cspd_btnode *node, cspd_vector *vec);
CSPD_API void         cspd_btree_bfs(cspd_btnode *node, cspd_queue *queue);
CSPD_API void         cspd_btree_invert(cspd_btnode *node);
CSPD_API i32          cspd_btree_height(cspd_btnode *node);
CSPD_API usize        cspd_btree_count(cspd_btnode *node);
CSPD_API void         cspd_btree_clear(cspd_btree *btree);

#define cspd_print_btree(type, vec)                                            \
    {                                                                          \
        printf("{ ");                                                          \
        for (usize i = 0; i < (vec)->size; ++i) {                              \
            cspd_btnode *_node = *(cspd_btnode **)cspd_vector_get(vec, i);     \
            cspd_print((*(type *)_node->data), " ");                           \
        }                                                                      \
        printf("} \n");                                                        \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_BTREE_H
