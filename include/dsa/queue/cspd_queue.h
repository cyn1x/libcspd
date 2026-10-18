/**
 * @file cspd_queue.h
 * @brief Queue data structures and algorithms.
 *
 * Typical implementation of a queue that is composed with a linked list data
 * structure.
 *
 * @see https://en.wikipedia.org/wiki/Queue_(abstract_data_type)
 */

#ifndef CSPD_QUEUE_H
#define CSPD_QUEUE_H

#include "cspd_exports.h"
#include "cspd_llist.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Data structure representation of a queue.
 *
 * @var cspd_llist::llist
 * Pointer to the underlying data structure.
 *
 * @var cspd_llnode::front
 * Pointer to the first node in the queue.
 *
 * @var cspd_llnode::back
 * Pointer to the last node in the queue.
 */
typedef struct cspd_queue_t
{
    cspd_llist   llist;

    cspd_llnode *front;
    cspd_llnode *back;

} cspd_queue;

/**
 * @brief Data structure for queue.
 *
 * Sets `data_size` to the given parameter, and sets the `front` and `back`
 * pointers to `NULL`.
 *
 * @param queue Pointer to the queue to be initialized.
 * @param data_size The size of the data type in bytes.
 *
 * @b Example
 * @snippet cspd_queue.test.c Initialize
 */
CSPD_API void cspd_queue_init(cspd_queue *queue, usize data_size);

/**
 * @brief Appends an element to the queue.
 *
 * Enqueue an element to the queue by appending it to the back of the queue.
 *
 * @note Uses a linked list to handle the first-in, first-out data structure.
 *
 * @param queue Pointer to the queue.
 * @param data Pointer to the data block.
 *
 * @b Example
 * @snippet cspd_queue.test.c Enqueue
 *
 * @see https://en.wikipedia.org/wiki/FIFO_(computing_and_electronics)
 */
CSPD_API void cspd_queue_enqueue(cspd_queue *queue, void *data);

/**
 * @brief Removes one element from the front of the queue.
 *
 * Deque one element from the queue by removing it from the front, and freeing
 * the associated memory. Sets the next element in the queue to `front` if the
 * queue is not empty.
 *
 * @param queue Pointer to the queue.
 *
 * @b Example
 * @snippet cspd_queue.test.c Deque
 */
CSPD_API void cspd_queue_deque(cspd_queue *queue);

/**
 * @brief Gets the pointer to the data block at the front of the queue.
 *
 * Reads the data block associated with the element at the front of the queue
 * without modifying the queue.
 *
 * @param queue Pointer to the queue.
 *
 * @returns Pointer to the data block at the front of the queue.
 *
 * @b Example
 * @snippet cspd_queue.test.c Peek
 */
CSPD_API void *cspd_queue_peek(cspd_queue *queue);

/**
 * @brief Removes all elements from the queue.
 *
 * Removes one element at a time from the queue until the queue is empty.
 *
 * @param queue Pointer to the queue.
 *
 * @b Example
 * @snippet cspd_queue.test.c Clear
 */
CSPD_API void cspd_queue_clear(cspd_queue *queue);

/**
 * @brief Declares a typed queue and its associated functions for a
 * given type.
 *
 * Generates a typedef for a `NAME_queue` type and the functions defined in
 * this header file.
 *
 * @param NAME  The name prefix used for the generated type and functions.
 * @param TYPE  The element type whose size is used to initialize the queue.
 *
 * @note This macro must be invoked at file scope, not inside a function.
 *
 * @par Example
 * @code
 *   cspd_queue_declare(i32, i32)
 *
 *   i32_queue q;
 *   i32_queue_init(&q);
 * @endcode
 */
#define cspd_queue_declare(NAME, TYPE)                                         \
                                                                               \
    typedef cspd_queue NAME##_queue;                                           \
                                                                               \
    static inline void NAME##_queue_init(NAME##_queue *queue)                  \
    {                                                                          \
        cspd_queue_init(queue, sizeof(TYPE));                                  \
    }                                                                          \
                                                                               \
    static inline void NAME##_queue_enqueue(NAME##_queue *queue, TYPE *data)   \
    {                                                                          \
        cspd_queue_enqueue(queue, (void *)data);                               \
    }                                                                          \
                                                                               \
    static inline void NAME##_queue_deque(NAME##_queue *queue)                 \
    {                                                                          \
        cspd_queue_deque(queue);                                               \
    }                                                                          \
                                                                               \
    static inline TYPE *NAME##_queue_peek(NAME##_queue *queue)                 \
    {                                                                          \
        return (TYPE *)cspd_queue_peek(queue);                                 \
    }                                                                          \
                                                                               \
    static inline void NAME##_queue_clear(NAME##_queue *queue)                 \
    {                                                                          \
        cspd_queue_clear(queue);                                               \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_QUEUE_H
