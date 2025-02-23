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

typedef struct stack_t
{
    llist_t  llist;

    lnode_t *top;
    lnode_t *bottom;

} stack_t;

LIBCSPD_API void  stack_init(stack_t *stack_t, size_t data_size);
LIBCSPD_API void  stack_push(stack_t *stack_t, void *data);
LIBCSPD_API void  stack_pop(stack_t *stack_t);
LIBCSPD_API void *stack_peek(stack_t *stack_t);
LIBCSPD_API void  stack_clear(stack_t *stack_t);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // STACK_H
