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

typedef struct cspd_queue
{
    cspd_llist   llist;

    cspd_llnode *front;
    cspd_llnode *back;

} cspd_queue;

LIBCSPD_API void  cspd_queue_init(cspd_queue *queue_t, size_t data_size);
LIBCSPD_API void  cspd_queue_enqueue(cspd_queue *queue_t, void *data);
LIBCSPD_API void  cspd_queue_deque(cspd_queue *queue_t);
LIBCSPD_API void *cspd_queue_peek(cspd_queue *queue_t);
LIBCSPD_API void  cspd_queue_clear(cspd_queue *queue_t);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_QUEUE_H
