#define LIBCSPD_EXPORTS

#include "queue.h"
#include "linked_list.h"
#include <stdlib.h>

void queue_init(queue *queue, size_t data_size)
{
    llist llist;
    llist_init(&llist, data_size);

    queue->llist = llist;
}

void queue_enqueue(queue *queue, void *data)
{
    llist_append(&queue->llist, data);

    if (queue->llist.head == queue->llist.tail) {
        queue->front = queue->llist.head;
    }
    queue->back = queue->llist.tail;
}

void queue_deque(queue *queue)
{
    lnode_t *tmp = queue->front->next;

    free(queue->front->data);
    free(queue->front);

    queue->llist.head = tmp;

    if (queue->llist.head == queue->llist.tail) {
        queue->back = queue->llist.head;
    }
    queue->front = queue->llist.head;
}

void *queue_peek(queue *queue) { return queue->front->data; }

void  queue_clear(queue *queue)
{
    while (queue->front != NULL) {
        queue_deque(queue);
    }
}
