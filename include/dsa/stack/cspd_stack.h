/**
 * @file cspd_stack.h
 * @brief Stack data structures and algorithms.
 *
 * Typical implementation of a stack that is composed with a linked list data
 * structure.
 *
 * @see https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
 */

#ifndef CSPD_STACK_H
#define CSPD_STACK_H

#include "cspd_exports.h"
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
 * @brief Prepends data to the stack.
 *
 * Pushes an element onto the stack by prepending it to the top of the stack.
 *
 * @note Uses a linked list to handle the last-in, first-out data structure.
 *
 * @param stack Pointer to the stack.
 * @param data Pointer to the data block.
 *
 * @b Example
 * @snippet cspd_stack.test.c Push
 */
CSPD_API void cspd_stack_push(cspd_stack *stack, void *data);

/**
 * @brief Removes one element from the top of the stack.
 *
 * Pop one element from the stack by removing it from the top, and freeing
 * the associated memory. Sets the next element in the stack to `top` if the
 * stack is not empty.
 *
 * @param stack Pointer to the stack.
 *
 * @b Example
 * @snippet cspd_stack.test.c Pop
 */
CSPD_API void cspd_stack_pop(cspd_stack *stack);

/**
 * @brief Gets the pointer to the data block at the top of the stack.
 *
 * Reads the data block associated with the element at the top of the stack
 * without modifying the stack.
 *
 * @param stack Pointer to the stack.
 *
 * @returns Pointer to the data block at the top of the stack.
 *
 * @b Example
 * @snippet cspd_stack.test.c Peek
 */
CSPD_API void *cspd_stack_peek(cspd_stack *stack);

/**
 * @brief Removes all elements from the stack.
 *
 * Pops one element at a time from the stack until the queue is empty.
 *
 * @param stack Pointer to the stack.
 *
 * @b Example
 * @snippet cspd_stack.test.c Clear
 */
CSPD_API void cspd_stack_clear(cspd_stack *stack);

/**
 * @brief Declares a typed stack and its associated functions for a
 * given type.
 *
 * Generates a typedef for a `NAME_stack` type and the functions defined in
 * this header file.
 *
 * @param NAME  The name prefix used for the generated type and functions.
 * @param TYPE  The element type whose size is used to initialize the stack.
 *
 * @note This macro must be invoked at file scope, not inside a function.
 *
 * @par Example
 * @code
 *   cspd_stack_declare(i32, i32);
 *
 *   i32_stack s;
 *   i32_stack_init(&s);
 * @endcode
 */
#define cspd_stack_declare(NAME, TYPE)                                         \
                                                                               \
    typedef cspd_stack NAME##_stack;                                           \
                                                                               \
    static inline void NAME##_stack_init(NAME##_stack *stack)                  \
    {                                                                          \
        cspd_stack_init(stack, sizeof(TYPE));                                  \
    }                                                                          \
                                                                               \
    static inline void NAME##_stack_push(NAME##_stack *stack, TYPE *data)      \
    {                                                                          \
        cspd_stack_push(stack, (void *)data);                                  \
    }                                                                          \
                                                                               \
    static inline void NAME##_stack_pop(NAME##_stack *stack)                   \
    {                                                                          \
        cspd_stack_pop(stack);                                                 \
    }                                                                          \
                                                                               \
    static inline TYPE *NAME##_stack_peek(NAME##_stack *stack)                 \
    {                                                                          \
        return (TYPE *)cspd_stack_peek(stack);                                 \
    }                                                                          \
                                                                               \
    static inline void NAME##_stack_clear(NAME##_stack *stack)                 \
    {                                                                          \
        cspd_stack_clear(stack);                                               \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_STACK_H
