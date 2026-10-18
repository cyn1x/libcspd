/**
 * @file cspd_bstree.h
 * @brief Binary search tree data structures and algorithms.
 *
 * @see https://en.wikipedia.org/wiki/Binary_search_tree
 */

#ifndef CSPD_BSTREE_H
#define CSPD_BSTREE_H

#include "cspd_exports.h"
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
 * Memory which has been allocated for the binary search tree node to store
 * data.
 *
 * @var cspd_bstnode::left
 * The binary search tree node's left pointer.
 *
 * @var cspd_bstnode::right
 * The binary search tree node's right pointer.
 */
typedef struct cspd_bstnode_t
{
    void                  *data;
    struct cspd_bstnode_t *left;
    struct cspd_bstnode_t *right;
} cspd_bstnode;

/**
 * @brief Data structure for the binary search tree.
 *
 * @var cspd_bstree::data_size
 * The size of the data in bytes being stored in the binary search tree.
 *
 * @var cspd_bstree::root
 * Pointer to the first node in the binary tree.
 */
typedef struct cspd_bstree_t
{
    usize         data_size;
    cspd_bstnode *root;
} cspd_bstree;

/**
 * @brief Initializes a new binary search tree.
 *
 * Sets `data_size` to the given parameter, and sets the `root` pointer to
 * `NULL`.
 *
 * @param bstree Pointer to the binary search tree to be initialized.
 * @param data_size The size of the data type in bytes.
 */
CSPD_API void cspd_bstree_init(cspd_bstree *bstree, usize data_size);

/**
 * @brief
 *
 *
 *
 * @param bstree
 * @param data
 *
 * @returns
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
 * Basic print function for primtive types that casts each element to the
 * specified type and prints it to standard output.
 *
 * @param type Type of data to be casted.
 * @param VECTOR The vector of nodes to be printed out.
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

/**
 * @brief Declares a typed binary search tree and its associated functions for a
 * given type.
 *
 * Generates a typedef for a `NAME_bstree` type and the functions defined in
 * this header file.
 *
 * @param NAME  The name prefix used for the generated type and functions.
 * @param TYPE  The element type whose size is used to initialize the binary
 * search tree.
 *
 * @note This macro must be invoked at file scope, not inside a function.
 *
 * @par Example
 * @code
 *   cspd_bstree_declare(i32, i32)
 *
 *   i32_bstree t;
 *   i32_bstree_init(&t);
 * @endcode
 */
#define cspd_bstree_declare(NAME, TYPE)                                        \
                                                                               \
    typedef cspd_bstnode NAME##_bstnode;                                       \
    typedef cspd_bstree  NAME##_bstree;                                        \
                                                                               \
    static inline void NAME##_bstree_init(NAME##_bstree *bstree)               \
    {                                                                          \
        cspd_bstree_init(bstree, sizeof(TYPE));                                \
    }                                                                          \
                                                                               \
    static inline NAME##_bstnode *NAME##_bstree_add(NAME##_bstree *bstree,     \
                                                    TYPE          *data)       \
    {                                                                          \
        return cspd_bstree_add(bstree, (void *)data);                          \
    }                                                                          \
                                                                               \
    static inline void cspd_bstree_clear(NAME##_bstree *bstree)                \
    {                                                                          \
        cspd_bstree_clear(bstree);                                             \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_BSTREE_H
