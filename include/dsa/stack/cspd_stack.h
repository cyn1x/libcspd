/**
 * @file cspd_stack.h
 */

#ifndef CSPD_STACK_H
#define CSPD_STACK_H

#include "cspd_defs.h"
#include "cspd_linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Data structure for `cspd_stack` type.
 *
 * @var cspd_llist::cspd_llist
 * Pointer to the underlying data structure.
 *
 * @var cspd_llist::top
 * Pointer to the first node in the stack.
 *
 * @var cspd_llist::bottom
 * Pointer to the last node in the stack.
 */
typedef struct cspd_stack_t
{
    cspd_llist   llist;

    cspd_llnode *top;
    cspd_llnode *bottom;

} cspd_stack;

/**
 * @brief Data structure representation of a stack.
 *
 * Sets `data_size` to the given parameter, and sets the `top` and `bottom`
 * pointers to `NULL`.
 *
 * @param stack Pointer to the stack to be initialized.
 * @param data_size The size of the data type in bytes.
 *
 * @b Example
 * @snippet cspd_stack.test.c Initialize
 */
CSPD_API void cspd_stack_init(cspd_stack *stack, usize data_size);

/**
 * @brief
 *
 *
 *
 * @param stack
 * @param data_size
 *
 * @b Example
 * @snippet cspd_stack.test.c Enqueue
 */
CSPD_API void cspd_stack_push(cspd_stack *stack, void *data);

/**
 * @brief
 *
 *
 *
 * @param stack
 * @param data_size
 *
 * @b Example
 * @snippet cspd_stack.test.c Pop
 */
CSPD_API void cspd_stack_pop(cspd_stack *stack);

/**
 * @brief
 *
 *
 *
 * @param stack
 *
 * @b Example
 * @snippet cspd_stack.test.c Peek
 */
CSPD_API void *cspd_stack_peek(cspd_stack *stack);

/**
 * @brief
 *
 *
 *
 * @param stack
 *
 * @b Example
 * @snippet cspd_stack.test.c Clear
 */
CSPD_API void cspd_stack_clear(cspd_stack *stack);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_STACK_H
