#define LIBCSPD_EXPORTS

#include "queue.h"
#include "cspd_linked_list.h"
#include <stdlib.h>

void cspd_queue_init(cspd_queue *queue_t, size_t data_size)
{
    cspd_llist llist;
    cspd_llist_init(&llist, data_size);

    queue_t->llist = llist;
}

void cspd_queue_enqueue(cspd_queue *queue_t, void *data)
{
    cspd_llist_append(&queue_t->llist, data);

    if (queue_t->llist.head == queue_t->llist.tail) {
        queue_t->front = queue_t->llist.head;
    }
    queue_t->back = queue_t->llist.tail;
}

void cspd_queue_deque(cspd_queue *queue_t)
{
    cspd_llnode *tmp = queue_t->front->next;

    free(queue_t->front->data);
    free(queue_t->front);

    queue_t->llist.head = tmp;

    if (queue_t->llist.head == queue_t->llist.tail) {
        queue_t->back = queue_t->llist.head;
    }
    queue_t->front = queue_t->llist.head;
}

void *cspd_queue_peek(cspd_queue *queue_t)
{
    return queue_t->front->data;
}

void cspd_queue_clear(cspd_queue *queue_t)
{
    while (queue_t->front != NULL) {
        cspd_queue_deque(queue_t);
    }
}
