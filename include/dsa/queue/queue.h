/**
 * @file queue.h
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "defs.h"
#include "linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct queue
{
    llist    llist;

    lnode_t *front;
    lnode_t *back;

    int (*_cmp)(const void *, const void *);

} queue;

LIBCSPD_API void  queue_init(queue *queue, size_t data_size);
LIBCSPD_API void  queue_enqueue(queue *queue, void *data);
LIBCSPD_API void  queue_deque(queue *queue);
LIBCSPD_API void *queue_peek(queue *queue);
LIBCSPD_API void  queue_clear(queue *queue);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // QUEUE_H
