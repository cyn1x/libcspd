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
    node_t *tmp = queue->llist.head->next;

    free(queue->llist.head->data);
    free(queue->llist.head);

    queue->llist.head = tmp;
    queue->front      = queue->llist.head;
    queue->back       = queue->llist.tail;

    if (queue->llist.head == queue->llist.tail) {
        queue->back = queue->llist.tail;
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
