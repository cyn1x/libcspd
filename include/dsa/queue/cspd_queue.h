/**
 * @file cspd_queue.h
 */

/**
 * @typedef struct cspd_queue
 *
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

/**
 * @fn void cspd_queue_init(cspd_queue *queue, size_t data_size)
 *
 * @brief Data structure for queue.
 *
 * Sets `data_size` to the given parameter, and sets the `front` and `back`
 * pointers to `NULL`.
 *
 * @param queue Pointer to the queue to be initialized.
 * @param data_size The size of the data type in bytes.
 *
 * @returns void
 *
 * @b Example
 * @snippet cspd_queue.test.c Initialize
 */

/**
 * @fn void cspd_queue_enqueue(cspd_queue *queue, void *data)
 *
 * @brief
 *
 *
 *
 * @param queue
 * @param data_size
 *
 * @returns void
 *
 * @b Example
 * @snippet cspd_queue.test.c Enqueue
 */

/**
 * @fn void cspd_queue_deque(cspd_queue *queue)
 *
 * @brief
 *
 *
 *
 * @param queue
 *
 * @returns void
 *
 * @b Example
 * @snippet cspd_queue.test.c Dequeue
 */

/**
 * @fn void *cspd_queue_peek(cspd_queue *queue)
 *
 * @brief
 *
 *
 *
 * @param queue
 *
 * @returns void
 *
 * @b Example
 * @snippet cspd_queue.test.c Peek
 */

/**
 * @fn void cspd_queue_clear(cspd_queue *queue)
 *
 * @brief
 *
 *
 *
 * @param queue
 *
 * @returns void
 *
 * @b Example
 * @snippet cspd_queue.test.c Clear
 */

#ifndef CSPD_QUEUE_H
#define CSPD_QUEUE_H

#include "cspd_defs.h"
#include "cspd_linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct cspd_queue_t
{
    cspd_llist   llist;

    cspd_llnode *front;
    cspd_llnode *back;

} cspd_queue;

CSPD_API void  cspd_queue_init(cspd_queue *queue, size_t data_size);
CSPD_API void  cspd_queue_enqueue(cspd_queue *queue, void *data);
CSPD_API void  cspd_queue_deque(cspd_queue *queue);
CSPD_API void *cspd_queue_peek(cspd_queue *queue);
CSPD_API void  cspd_queue_clear(cspd_queue *queue);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_QUEUE_H
