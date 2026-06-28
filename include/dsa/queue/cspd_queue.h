/**
 * @file cspd_queue.h
 */

#ifndef CSPD_QUEUE_H
#define CSPD_QUEUE_H

#include "cspd_defs.h"
#include "cspd_linked_list.h"

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
 * @brief
 *
 *
 *
 * @param queue
 * @param data_size
 *
 * @b Example
 * @snippet cspd_queue.test.c Enqueue
 */
CSPD_API void cspd_queue_enqueue(cspd_queue *queue, void *data);

/**
 * @brief
 *
 *
 *
 * @param queue
 *
 * @b Example
 * @snippet cspd_queue.test.c Dequeue
 */
CSPD_API void cspd_queue_deque(cspd_queue *queue);

/**
 * @brief
 *
 *
 *
 * @param queue
 *
 * @b Example
 * @snippet cspd_queue.test.c Peek
 */
CSPD_API void *cspd_queue_peek(cspd_queue *queue);

/**
 * @brief
 *
 *
 *
 * @param queue
 *
 * @b Example
 * @snippet cspd_queue.test.c Clear
 */
CSPD_API void cspd_queue_clear(cspd_queue *queue);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_QUEUE_H
