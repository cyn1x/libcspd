/**
 * @file cspd_stack.h
 */

/**
 * @typedef struct cspd_stack
 *
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

/**
 * @fn void cspd_stack_init(cspd_stack *stack, usize data_size)
 *
 * @brief Data structure representation of a stack.
 *
 * Sets `data_size` to the given parameter, and sets the `top` and `bottom`
 * pointers to `NULL`.
 *
 * @param stack Pointer to the stack to be initialized.
 * @param data_size The size of the data type in bytes.
 *
 * @returns void
 *
 * @b Example
 * @snippet cspd_stack.test.c Initialize
 */

/**
 * @fn void cspd_stack_push(cspd_stack *stack, void *data)
 *
 * @brief
 *
 *
 *
 * @param stack
 * @param data_size
 *
 * @returns void
 *
 * @b Example
 * @snippet cspd_stack.test.c Enqueue
 */

/**
 * @fn void cspd_stack_pop(cspd_stack *stack)
 *
 * @brief
 *
 *
 *
 * @param stack
 * @param data_size
 *
 * @returns void
 *
 * @b Example
 * @snippet cspd_stack.test.c Pop
 */

/**
 * @fn void *cspd_stack_peek(cspd_stack *stack)
 *
 * @brief
 *
 *
 *
 * @param stack
 *
 * @returns void
 *
 * @b Example
 * @snippet cspd_stack.test.c Peek
 */

/**
 * @fn void cspd_stack_clear(cspd_stack *stack)
 *
 * @brief
 *
 *
 *
 * @param stack
 *
 * @returns void
 *
 * @b Example
 * @snippet cspd_stack.test.c Clear
 */

#ifndef CSPD_STACK_H
#define CSPD_STACK_H

#include "cspd_defs.h"
#include "cspd_linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct cspd_stack_t
{
    cspd_llist   llist;

    cspd_llnode *top;
    cspd_llnode *bottom;

} cspd_stack;

CSPD_API void  cspd_stack_init(cspd_stack *stack, usize data_size);
CSPD_API void  cspd_stack_push(cspd_stack *stack, void *data);
CSPD_API void  cspd_stack_pop(cspd_stack *stack);
CSPD_API void *cspd_stack_peek(cspd_stack *stack);
CSPD_API void  cspd_stack_clear(cspd_stack *stack);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_STACK_H
