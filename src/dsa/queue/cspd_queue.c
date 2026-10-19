#define CSPD_EXPORTS

#include "cspd_queue.h"
#include "cspd_mem.h"

void cspd_queue_init(cspd_queue *queue, usize data_size)
{
    cspd_list_init(&queue->list, data_size);
    queue->front = NULL;
    queue->back  = NULL;
}

void cspd_queue_enqueue(cspd_queue *queue, void *data)
{
    cspd_list_append(&queue->list, data);

    if (queue->list.head == queue->list.tail) {
        queue->front = queue->list.head;
    }
    queue->back = queue->list.tail;
}

void cspd_queue_deque(cspd_queue *queue)
{
    if (queue->front == NULL) return;

    cspd_lnode *tmp = queue->front->next;

    cspd_free(queue->front->data);
    cspd_free(queue->front);

    queue->list.head = tmp;

    if (queue->list.head == queue->list.tail) {
        queue->back = queue->list.head;
    }
    queue->front = queue->list.head;
}

void *cspd_queue_peek(cspd_queue *queue)
{
    return queue->front->data;
}

void cspd_queue_clear(cspd_queue *queue)
{
    while (queue->front != NULL) {
        cspd_queue_deque(queue);
    }
}
