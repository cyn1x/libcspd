/**
 * @file stack.h
 */

#ifndef STACK_H
#define STACK_H

#include "defs.h"
#include "linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct stack
{
    llist   llist;

    node_t *top;
    node_t *bottom;

    int (*_cmp)(const void *, const void *);

} stack;

LIBCSPD_API void  stack_init(stack *stack, size_t data_size);
LIBCSPD_API void  stack_push(stack *stack, void *data);
LIBCSPD_API void  stack_pop(stack *stack);
LIBCSPD_API void *stack_peek(stack *stack);
LIBCSPD_API void  stack_clear(stack *stack);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // STACK_H
