/**
 * @file cspd_bst.h
 * @brief Binary search tree data structures and algorithms.
 *
 * @see https://en.wikipedia.org/wiki/Binary_search_tree
 */

#ifndef CSPD_BST_H
#define CSPD_BST_H

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
 * @var cspd_bst::data_size
 * The size of the data in bytes being stored in the binary search tree.
 *
 * @var cspd_bst::root
 * Pointer to the first node in the binary tree.
 */
typedef struct cspd_bst_t
{
    usize         data_size;
    cspd_bstnode *root;
} cspd_bst;

/**
 * @brief Initializes a new binary search tree.
 *
 * Sets `data_size` to the given parameter, and sets the `root` pointer to
 * `NULL`.
 *
 * @param bst Pointer to the binary search tree to be initialized.
 * @param data_size The size of the data type in bytes.
 */
CSPD_API void cspd_bst_init(cspd_bst *bst, usize data_size);

/**
 * @brief
 *
 *
 *
 * @param bst
 * @param data
 *
 * @returns
 */
CSPD_API cspd_bstnode *cspd_bst_add(cspd_bst *bst, void *data);

/**
 * @brief
 *
 *
 *
 * @param bst
 */
CSPD_API void cspd_bst_clear(cspd_bst *bst);

/**
 * @brief Prints the contents of the binary search tree.
 *
 * Basic print function for primtive types that casts each element to the
 * specified type and prints it to standard output.
 *
 * @param type Type of data to be casted.
 * @param VECTOR The vector of nodes to be printed out.
 */
#define cspd_print_bst(TYPE, VECTOR)                                           \
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
 * Generates a typedef for a `NAME_bst` type and the functions defined in
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
 *   cspd_bst_declare(i32, i32)
 *
 *   i32_bst t;
 *   i32_bst_init(&t);
 * @endcode
 */
#define cspd_bst_declare(NAME, TYPE)                                           \
                                                                               \
    typedef cspd_bstnode NAME##_bst;                                           \
    typedef cspd_bst     NAME##_bst;                                           \
                                                                               \
    static inline void NAME##_bst_init(NAME##_bst *bst)                        \
    {                                                                          \
        cspd_bst_init(bst, sizeof(TYPE));                                      \
    }                                                                          \
                                                                               \
    static inline NAME##_bstnode *NAME##_bst_add(NAME##_bst *bst, TYPE *data)  \
    {                                                                          \
        return cspd_bst_add(bst, (void *)data);                                \
    }                                                                          \
                                                                               \
    static inline void cspd_bst_clear(NAME##_bst *bst)                         \
    {                                                                          \
        cspd_bst_clear(bst);                                                   \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_BST_H
