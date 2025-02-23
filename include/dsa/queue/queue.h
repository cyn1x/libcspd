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

typedef struct queue_t
{
    llist_t  llist;

    lnode_t *front;
    lnode_t *back;

} queue_t;

LIBCSPD_API void  queue_init(queue_t *queue_t, size_t data_size);
LIBCSPD_API void  queue_enqueue(queue_t *queue_t, void *data);
LIBCSPD_API void  queue_deque(queue_t *queue_t);
LIBCSPD_API void *queue_peek(queue_t *queue_t);
LIBCSPD_API void  queue_clear(queue_t *queue_t);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // QUEUE_H
