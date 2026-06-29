/**
 * @file cspd_btree.h
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

/**
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
typedef struct cspd_btnode_t
{
    void                 *data;
    struct cspd_btnode_t *left;
    struct cspd_btnode_t *right;

} cspd_btnode;

/**
 * @brief Data structure for binary tree.
 *
 * @var cspd_btree::data_size
 * The size of the data in bytes being stored in the nodes that reside in the
 * binary tree.
 *
 * @var cspd_btree::root
 * Pointer to the first node in the binary tree.
 */
typedef struct cspd_btree_t
{
    usize        data_size;
    cspd_btnode *root;

} cspd_btree;

/**
 * @brief
 *
 *
 *
 * @param btree
 * @param data_size
 */
CSPD_API void cspd_btree_init(cspd_btree *btree, usize data_size);

/**
 * @brief
 *
 *
 *
 * @param btree
 * @param data
 */
CSPD_API cspd_btnode *cspd_btree_add(cspd_btree *btree, cspd_btnode **leaf,
                                     void *data);

/**
 * @brief
 *
 *
 *
 * @param btree
 * @param parent
 */
CSPD_API cspd_btnode *cspd_btree_insert(cspd_btree *btree, cspd_btnode **parent,
                                        void *data);

/**
 * @brief
 *
 *
 *
 * @param node
 * @param vec
 */
CSPD_API void cspd_btree_preorder(cspd_btnode *node, cspd_vector *vec);

/**
 * @brief
 *
 *
 *
 * @param node
 * @param vec
 */
CSPD_API void cspd_btree_inorder(cspd_btnode *node, cspd_vector *vec);

/**
 * @brief
 *
 *
 *
 * @param node
 * @param vec
 */
CSPD_API void cspd_btree_postorder(cspd_btnode *node, cspd_vector *vec);

/**
 * @brief
 *
 *
 *
 * @param node
 * @param vec
 */
CSPD_API void cspd_btree_dfs(cspd_btnode *node, cspd_vector *vec);

/**
 * @brief
 *
 *
 *
 * @param node
 * @param vec
 */
CSPD_API void cspd_btree_bfs(cspd_btnode *node, cspd_queue *queue);

/**
 * @brief
 *
 *
 *
 * @param node
 */
CSPD_API void cspd_btree_invert(cspd_btnode *node);

/**
 * @brief
 *
 *
 *
 * @param node
 */
CSPD_API i32 cspd_btree_height(cspd_btnode *node);

/**
 * @brief
 *
 *
 *
 * @param node
 */
CSPD_API usize cspd_btree_count(cspd_btnode *node);

/**
 * @brief
 *
 *
 *
 * @param btree
 */
CSPD_API void cspd_btree_clear(cspd_btree *btree);

/**
 * @brief Prints the contents of the binary tree.
 *
 *
 *
 * @param type Type of data to be casted.
 * @param vec
 */
#define cspd_print_btree(TYPE, VECTOR)                                         \
    {                                                                          \
        printf("{ ");                                                          \
        for (usize i = 0; i < (VECTOR)->size; ++i) {                           \
            cspd_btnode *_node = *(cspd_btnode **)cspd_vector_get(VECTOR, i);  \
            cspd_print((*(TYPE *)_node->data), " ");                           \
        }                                                                      \
        printf("} \n");                                                        \
    }

/**
 * @brief Declares a typed binary tree and its associated functions for a
 * given type.
 *
 * Generates a typedef for a `NAME_btree` and `NAME_btnode` type, and the
 * functions defined in this header file.
 *
 * @param NAME  The name prefix used for the generated type and functions.
 * @param TYPE  The element type whose size is used to initialize the binary
 * tree.
 *
 * @note This macro must be invoked at file scope, not inside a function.
 *
 * @warning A `NAME_vector` and `NAME_queue` must be declared before declaring a
 * `NAME_btree`.
 *
 * @par Example:
 * @code
 *   cspd_btree_declare(i32, i32);
 *
 *   i32_btree t;
 *   i32_btree_init(&t);
 * @endcode
 */
#define cspd_btree_declare(NAME, TYPE)                                         \
                                                                               \
    typedef cspd_btnode NAME##_btnode;                                         \
    typedef cspd_btree  NAME##_btree;                                          \
                                                                               \
    static inline void  NAME##_btree_init(NAME##_btree *btree)                 \
    {                                                                          \
        cspd_btree_init(btree, sizeof(TYPE));                                  \
    }                                                                          \
                                                                               \
    static inline NAME##_btnode *NAME##_btree_add(                             \
        NAME##_btree *btree, NAME##_btnode **leaf, TYPE *data)                 \
    {                                                                          \
        return cspd_btree_add(btree, leaf, (void *)data);                      \
    }                                                                          \
                                                                               \
    static inline NAME##_btnode *NAME##_btree_insert(                          \
        NAME##_btree *btree, NAME##_btnode **parent, TYPE *data)               \
    {                                                                          \
        return cspd_btree_insert(btree, parent, (void *)data);                 \
    }                                                                          \
                                                                               \
    static inline void NAME##_btree_preorder(NAME##_btnode *node,              \
                                             NAME##_vector *vec)               \
    {                                                                          \
        cspd_btree_preorder(node, vec);                                        \
    }                                                                          \
                                                                               \
    static inline void NAME##_btree_inorder(NAME##_btnode *node,               \
                                            NAME##_vector *vec)                \
    {                                                                          \
        cspd_btree_inorder(node, vec);                                         \
    }                                                                          \
                                                                               \
    static inline void NAME##_btree_postorder(NAME##_btnode *node,             \
                                              NAME##_vector *vec)              \
    {                                                                          \
        cspd_btree_postorder(node, vec);                                       \
    }                                                                          \
                                                                               \
    static inline void NAME##_btree_dfs(NAME##_btnode *node,                   \
                                        NAME##_vector *vec)                    \
    {                                                                          \
        cspd_btree_dfs(node, vec);                                             \
    }                                                                          \
                                                                               \
    static inline void NAME##_btree_bfs(NAME##_btnode *node,                   \
                                        NAME##_queue  *queue)                  \
    {                                                                          \
        cspd_btree_bfs(node, queue);                                           \
    }                                                                          \
                                                                               \
    static inline void NAME##_btree_invert(NAME##_btnode *node)                \
    {                                                                          \
        cspd_btree_invert(node);                                               \
    }                                                                          \
                                                                               \
    static inline i32 NAME##_btree_height(NAME##_btnode *node)                 \
    {                                                                          \
        return cspd_btree_height(node);                                        \
    }                                                                          \
                                                                               \
    static inline usize NAME##_btree_count(NAME##_btnode *node)                \
    {                                                                          \
        return cspd_btree_count(node);                                         \
    }                                                                          \
                                                                               \
    static inline void NAME##_btree_clear(NAME##_btree *btree)                 \
    {                                                                          \
        cspd_btree_clear(btree);                                               \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_BTREE_H
