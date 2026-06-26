#define CSPD_EXPORTS

#include "cspd_queue.h"
#include "cspd_linked_list.h"
#include "cspd_mem.h"

void cspd_queue_init(cspd_queue *queue, size_t data_size)
{
    cspd_llist llist;
    cspd_llist_init(&llist, data_size);

    queue->llist = llist;
}

void cspd_queue_enqueue(cspd_queue *queue, void *data)
{
    cspd_llist_append(&queue->llist, data);

    if (queue->llist.head == queue->llist.tail) {
        queue->front = queue->llist.head;
    }
    queue->back = queue->llist.tail;
}

void cspd_queue_deque(cspd_queue *queue)
{
    cspd_llnode *tmp = queue->front->next;

    cspd_free(queue->front->data);
    cspd_free(queue->front);

    queue->llist.head = tmp;

    if (queue->llist.head == queue->llist.tail) {
        queue->back = queue->llist.head;
    }
    queue->front = queue->llist.head;
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
