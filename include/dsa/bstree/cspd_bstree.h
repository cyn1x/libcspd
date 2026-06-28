/**
 * @file cspd_bstree.h
 */

#ifndef CSPD_BSTREE_H
#define CSPD_BSTREE_H

#include "cspd_defs.h"
#include "cspd_types.h"

#ifdef __clang__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Data structure for the binary search tree node.
 *
 * @var cspd_bstnode::data
 *
 *
 * @var cspd_bstnode::left
 *
 *
 * @var cspd_bstnode::right
 *
 */
typedef struct cspd_bstnode_t
{
    void           *data;
    struct bstnode *left;
    struct bstnode *right;
} cspd_bstnode;

/**
 * @brief Data structure for the binary search tree.
 *
 * @var cspd_bstree::root
 *
 *
 * @var cspd_bstree::data_size
 * The size of the data in bytes being stored in the binary search tree.
 */
typedef struct cspd_bstree_t
{
    cspd_bstnode *root;
    usize         data_size;
} cspd_bstree;

/**
 * @brief
 *
 *
 *
 * @param bstree
 * @param data_size
 */
CSPD_API void cspd_bstree_init(cspd_bstree *bstree, usize data_size);

/**
 * @brief
 *
 *
 *
 * @param bstree
 * @param data
 */
CSPD_API cspd_bstnode *cspd_bstree_add(cspd_bstree *bstree, void *data);

/**
 * @brief
 *
 *
 *
 * @param bstree
 */
CSPD_API void cspd_bstree_clear(cspd_bstree *bstree);

/**
 * @brief Prints the contents of the binary search tree.
 *
 *
 *
 * @param type Type of data to be casted.
 * @param vec
 */
#define cspd_print_bstree(TYPE, VECTOR)                                        \
    {                                                                          \
        printf("{ ");                                                          \
        for (usize i = 0; i < (VECTOR)->size; ++i) {                           \
            cspd_bstnode *_node =                                              \
                *(cspd_bstnode **)cspd_vector_get(VECTOR, i);                  \
            cspd_print((*(TYPE *)_node->data), " ");                           \
        }                                                                      \
        printf("} \n");                                                        \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_BSTREE_H
