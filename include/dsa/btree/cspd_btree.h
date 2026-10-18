/**
 * @file cspd_btree.h
 * @brief Binary tree data structures and algorithms.
 *
 * @see https://en.wikipedia.org/wiki/Binary_tree
 */

#ifndef CSPD_BTREE_H
#define CSPD_BTREE_H

#include "cspd_exports.h"
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
 * @brief Initializes a new binary tree.
 *
 * Sets `data_size` to the given parameter, and sets the `root` pointer to
 * `NULL`.
 *
 * @param btree Pointer to the binary search tree to be initialized.
 * @param data_size The size of the data type in bytes.
 */
CSPD_API void cspd_btree_init(cspd_btree *btree, usize data_size);

/**
 * @brief Adds a node to the binary tree.
 *
 * Adds a node to the binary tree as a child of a parent node's `left` or
 * `right` pointers, denoted as `leaf`.
 *
 * @warning The `leaf` pointer must be `NULL` as overwriting nodes is not valid.
 *
 * @param btree Pointer to the binary tree.
 * @param data Pointer to the data to be added.
 *
 * @returns Pointer to the node on success, or `NULL` on failure.
 *
 * @b Example
 * @snippet cspd_btree.test.c Adding nodes
 */
CSPD_API cspd_btnode *cspd_btree_add(cspd_btree *btree, cspd_btnode **leaf,
                                     void *data);

/**
 * @brief Inserts a node into the binary tree.
 *
 * Inserts a node into the binary tree as a child to the given `parent` node. If
 * `parent` has only one child, then the new node will be added as the second
 * child to one of the unoccupied `left` or `right` pointers. If `parent` has
 * two children, then the new node will be assigned to the `left` pointer of
 * `parent` by default. The new node's `left` or `right` pointer will then
 * reference the node that `parent` was pointing to prior to insertion.
 *
 * @param btree Pointer to the binary tree.
 * @param parent Pointer to the parent of the new node.
 *
 * @returns Pointer to the node on success, or `NULL` on failure.
 *
 * @b Example
 * @snippet cspd_btree.test.c Insertion
 */
CSPD_API cspd_btnode *cspd_btree_insert(cspd_btree *btree, cspd_btnode **parent,
                                        void *data);

/**
 * @brief Pre-order traversal of a binary tree.
 *
 * Performs a pre-order traversal of a binary tree and pushes a reference to
 * each node to the given `vec` in the order they are visited.
 *
 * @param node Pointer to the node to start the pre-order traversal from.
 * @param vec Pointer to the initialized vector to store the node references.
 *
 * @see https://en.wikipedia.org/wiki/Tree_traversal#Pre-order,_NLR
 */
CSPD_API void cspd_btree_preorder(cspd_btnode *node, cspd_vector *vec);

/**
 * @brief Post-order traversal of a binary tree.
 *
 * Performs an in-order traversal of a binary tree and pushes a reference to
 * each node to the given `vec` in the order they are visited.
 *
 * @param node Pointer to the node to start the in-order traversal from.
 * @param vec Pointer to the initialized vector to store the node references.
 *
 * @see https://en.wikipedia.org/wiki/Tree_traversal#In-order,_LNR
 */
CSPD_API void cspd_btree_inorder(cspd_btnode *node, cspd_vector *vec);

/**
 * @brief Post-order traversal of a binary tree.
 *
 * Performs a post-order traversal of a binary tree and pushes a reference to
 * each node to the given `vec` in the order they are visited.
 *
 * @param node Pointer to the node to start the post-order traversal from.
 * @param vec Pointer to the initialized vector to store the node references.
 *
 * @see https://en.wikipedia.org/wiki/Tree_traversal#Post-order,_LRN
 */
CSPD_API void cspd_btree_postorder(cspd_btnode *node, cspd_vector *vec);

/**
 * @brief Depth-first search of a binary tree.
 *
 * Traverses a binary tree in level-order by visiting all of the nodes at each
 * level before moving to the next level.
 *
 * @param node Pointer to the node to start the depth-first search traversal.
 * @param vec Pointer to the initialized vector to store the node references.
 *
 * @see https://en.wikipedia.org/wiki/Tree_traversal#Breadth-first_search
 */
CSPD_API void cspd_btree_dfs(cspd_btnode *node, cspd_vector *vec);

/**
 * @brief Breadth-first search of a binary tree.
 *
 * Performs a traversal of a binary tree in topological order. Adds each node to
 * the given `vec` in the order they are visited.
 *
 * @param node Pointer to the node to start the breadth-first search traversal.
 * @param vec Pointer to the initialized vector to store the node references.
 *
 * @see https://en.wikipedia.org/wiki/Tree_traversal#Depth-first_search
 */
CSPD_API void cspd_btree_bfs(cspd_btnode *node, cspd_queue *queue);

/**
 * @brief Inverts a binary tree.
 *
 * Inverts a binary tree, or part of a binary tree, by swapping each `left` and
 * `right` pointer from the given node until each node after `node` has been
 * traversed.
 *
 * @param node Pointer to the node of the binary tree to invert.
 *
 * @b Example
 * @snippet cspd_btree.test.c Inversion
 */
CSPD_API void cspd_btree_invert(cspd_btnode *node);

/**
 * @brief Calculates the height of a binary tree.
 *
 * Performs a depth-first traversal of a binary tree to determine the height
 * from the given node.
 *
 * @note Pass in the `root` of the binary tree to calculate the total height.
 *
 * @param node The node to measure the height from.
 *
 * @returns The height of the binary tree from the given `node` pointer.
 *
 * @b Example
 * @snippet cspd_btree.test.c Calculating height
 *
 * @see https://en.wikipedia.org/wiki/Binary_tree#Properties_of_binary_trees
 */
CSPD_API i32 cspd_btree_height(cspd_btnode *node);

/**
 * @brief Counts the number of elements in a binary tree.
 *
 * Visits each node in the binary tree in topological order and adds them to a
 * vector. The size of the vector determines the total number of nodes in the
 * binary tree.
 *
 * @param btree The binary tree containing the nodes to be counted.
 *
 * @returns The number of nodes in the binary tree.
 */
CSPD_API usize cspd_btree_count(cspd_btnode *node);

/**
 * @brief Clears a binary tree.
 *
 * Clears a binary tree by freeing the memory of each node.
 *
 * @param btree The binary tree to be cleared.
 */
CSPD_API void cspd_btree_clear(cspd_btree *btree);

/**
 * @brief Prints the contents of the binary tree.
 *
 * Basic print function for primtive types that casts each element to the
 * specified type and prints it to standard output.
 *
 * @param TYPE Type of data to be casted.
 * @param VECTOR The vector of nodes to be printed out.
 */
#define cspd_print_btree(TYPE, VEC)                                            \
    {                                                                          \
        printf("{ ");                                                          \
        for (usize i = 0; i < (VEC)->size; ++i) {                              \
            cspd_btnode *_node = ((cspd_btnode **)(VEC)->data)[i];             \
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
 * @par Example
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
    static inline void NAME##_btree_init(NAME##_btree *btree)                  \
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
