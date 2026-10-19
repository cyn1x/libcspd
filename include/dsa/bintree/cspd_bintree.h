/**
 * @file cspd_bintree.h
 * @brief Binary tree data structures and algorithms.
 *
 * @see https://en.wikipedia.org/wiki/Binary_tree
 */

#ifndef CSPD_BINTREE_H
#define CSPD_BINTREE_H

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
 * @var cspd_bintree::data_size
 * The size of the data in bytes being stored in the nodes that reside in the
 * binary tree.
 *
 * @var cspd_bintree::root
 * Pointer to the first node in the binary tree.
 */
typedef struct cspd_bintree_t
{
    usize        data_size;
    cspd_btnode *root;

} cspd_bintree;

/**
 * @brief Initializes a new binary tree.
 *
 * Sets `data_size` to the given parameter, and sets the `root` pointer to
 * `NULL`.
 *
 * @param bintree Pointer to the binary search tree to be initialized.
 * @param data_size The size of the data type in bytes.
 */
CSPD_API void cspd_bintree_init(cspd_bintree *bintree, usize data_size);

/**
 * @brief Adds a node to the binary tree.
 *
 * Adds a node to the binary tree as a child of a parent node's `left` or
 * `right` pointers, denoted as `leaf`.
 *
 * @warning The `leaf` pointer must be `NULL` as overwriting nodes is not valid.
 *
 * @param bintree Pointer to the binary tree.
 * @param data Pointer to the data to be added.
 *
 * @returns Pointer to the node on success, or `NULL` on failure.
 *
 * @b Example
 * @snippet cspd_bintree.test.c Adding nodes
 */
CSPD_API cspd_btnode *cspd_bintree_add(cspd_bintree *bintree,
                                       cspd_btnode **leaf, void *data);

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
 * @param bintree Pointer to the binary tree.
 * @param parent Pointer to the parent of the new node.
 *
 * @returns Pointer to the node on success, or `NULL` on failure.
 *
 * @b Example
 * @snippet cspd_bintree.test.c Insertion
 */
CSPD_API cspd_btnode *cspd_bintree_insert(cspd_bintree *bintree,
                                          cspd_btnode **parent, void *data);

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
CSPD_API void cspd_bintree_preorder(cspd_btnode *node, cspd_vector *vec);

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
CSPD_API void cspd_bintree_inorder(cspd_btnode *node, cspd_vector *vec);

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
CSPD_API void cspd_bintree_postorder(cspd_btnode *node, cspd_vector *vec);

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
CSPD_API void cspd_bintree_dfs(cspd_btnode *node, cspd_vector *vec);

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
CSPD_API void cspd_bintree_bfs(cspd_btnode *node, cspd_queue *queue);

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
 * @snippet cspd_bintree.test.c Inversion
 */
CSPD_API void cspd_bintree_invert(cspd_btnode *node);

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
 * @snippet cspd_bintree.test.c Calculating height
 *
 * @see https://en.wikipedia.org/wiki/Binary_tree#Properties_of_binary_trees
 */
CSPD_API i32 cspd_bintree_height(cspd_btnode *node);

/**
 * @brief Counts the number of elements in a binary tree.
 *
 * Visits each node in the binary tree in topological order and adds them to a
 * vector. The size of the vector determines the total number of nodes in the
 * binary tree.
 *
 * @param bintree The binary tree containing the nodes to be counted.
 *
 * @returns The number of nodes in the binary tree.
 */
CSPD_API usize cspd_bintree_count(cspd_btnode *node);

/**
 * @brief Clears a binary tree.
 *
 * Clears a binary tree by freeing the memory of each node.
 *
 * @param bintree The binary tree to be cleared.
 */
CSPD_API void cspd_bintree_clear(cspd_bintree *bintree);

/**
 * @brief Prints the contents of the binary tree.
 *
 * Basic print function for primtive types that casts each element to the
 * specified type and prints it to standard output.
 *
 * @param TYPE Type of data to be casted.
 * @param VECTOR The vector of nodes to be printed out.
 */
#define cspd_print_bintree(TYPE, VEC)                                          \
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
 * Generates a typedef for a `NAME_bintree` and `NAME_btnode` type, and the
 * functions defined in this header file.
 *
 * @param NAME  The name prefix used for the generated type and functions.
 * @param TYPE  The element type whose size is used to initialize the binary
 * tree.
 *
 * @note This macro must be invoked at file scope, not inside a function.
 *
 * @warning A `NAME_vector` and `NAME_queue` must be declared before declaring a
 * `NAME_bintree`.
 *
 * @par Example
 * @code
 *   cspd_bintree_declare(i32, i32);
 *
 *   i32_bintree t;
 *   i32_bintree_init(&t);
 * @endcode
 */
#define cspd_bintree_declare(NAME, TYPE)                                       \
                                                                               \
    typedef cspd_btnode  NAME##_btnode;                                        \
    typedef cspd_bintree NAME##_bintree;                                       \
                                                                               \
    static inline void NAME##_bintree_init(NAME##_bintree *bintree)            \
    {                                                                          \
        cspd_bintree_init(bintree, sizeof(TYPE));                              \
    }                                                                          \
                                                                               \
    static inline NAME##_btnode *NAME##_bintree_add(                           \
        NAME##_bintree *bintree, NAME##_btnode **leaf, TYPE *data)             \
    {                                                                          \
        return cspd_bintree_add(bintree, leaf, (void *)data);                  \
    }                                                                          \
                                                                               \
    static inline NAME##_btnode *NAME##_bintree_insert(                        \
        NAME##_bintree *bintree, NAME##_btnode **parent, TYPE *data)           \
    {                                                                          \
        return cspd_bintree_insert(bintree, parent, (void *)data);             \
    }                                                                          \
                                                                               \
    static inline void NAME##_bintree_preorder(NAME##_btnode *node,            \
                                               NAME##_vector *vec)             \
    {                                                                          \
        cspd_bintree_preorder(node, vec);                                      \
    }                                                                          \
                                                                               \
    static inline void NAME##_bintree_inorder(NAME##_btnode *node,             \
                                              NAME##_vector *vec)              \
    {                                                                          \
        cspd_bintree_inorder(node, vec);                                       \
    }                                                                          \
                                                                               \
    static inline void NAME##_bintree_postorder(NAME##_btnode *node,           \
                                                NAME##_vector *vec)            \
    {                                                                          \
        cspd_bintree_postorder(node, vec);                                     \
    }                                                                          \
                                                                               \
    static inline void NAME##_bintree_dfs(NAME##_btnode *node,                 \
                                          NAME##_vector *vec)                  \
    {                                                                          \
        cspd_bintree_dfs(node, vec);                                           \
    }                                                                          \
                                                                               \
    static inline void NAME##_bintree_bfs(NAME##_btnode *node,                 \
                                          NAME##_queue  *queue)                \
    {                                                                          \
        cspd_bintree_bfs(node, queue);                                         \
    }                                                                          \
                                                                               \
    static inline void NAME##_bintree_invert(NAME##_btnode *node)              \
    {                                                                          \
        cspd_bintree_invert(node);                                             \
    }                                                                          \
                                                                               \
    static inline i32 NAME##_bintree_height(NAME##_btnode *node)               \
    {                                                                          \
        return cspd_bintree_height(node);                                      \
    }                                                                          \
                                                                               \
    static inline usize NAME##_bintree_count(NAME##_btnode *node)              \
    {                                                                          \
        return cspd_bintree_count(node);                                       \
    }                                                                          \
                                                                               \
    static inline void NAME##_bintree_clear(NAME##_bintree *bintree)           \
    {                                                                          \
        cspd_bintree_clear(bintree);                                           \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_BINTREE_H
