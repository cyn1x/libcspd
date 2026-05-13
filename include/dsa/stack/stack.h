/**
 * @file stack.h
 */

#ifndef CSPD_STACK_H
#define CSPD_STACK_H

#include "cspd_defs.h"
#include "cspd_linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct cspd_stack
{
    cspd_llist   llist;

    cspd_llnode *top;
    cspd_llnode *bottom;

} cspd_stack;

LIBCSPD_API void  cspd_stack_init(cspd_stack *stack_t, size_t data_size);
LIBCSPD_API void  cspd_stack_push(cspd_stack *stack_t, void *data);
LIBCSPD_API void  cspd_stack_pop(cspd_stack *stack_t);
LIBCSPD_API void *cspd_stack_peek(cspd_stack *stack_t);
LIBCSPD_API void  cspd_stack_clear(cspd_stack *stack_t);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_STACK_H
