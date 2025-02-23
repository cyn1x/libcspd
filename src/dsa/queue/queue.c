#define LIBCSPD_EXPORTS

#include "queue.h"
#include "linked_list.h"
#include <stdlib.h>

void queue_init(queue_t *queue_t, size_t data_size)
{
    llist_t llist;
    llist_init(&llist, data_size);

    queue_t->llist = llist;
}

void queue_enqueue(queue_t *queue_t, void *data)
{
    llist_append(&queue_t->llist, data);

    if (queue_t->llist.head == queue_t->llist.tail) {
        queue_t->front = queue_t->llist.head;
    }
    queue_t->back = queue_t->llist.tail;
}

void queue_deque(queue_t *queue_t)
{
    llnode_t *tmp = queue_t->front->next;

    free(queue_t->front->data);
    free(queue_t->front);

    queue_t->llist.head = tmp;

    if (queue_t->llist.head == queue_t->llist.tail) {
        queue_t->back = queue_t->llist.head;
    }
    queue_t->front = queue_t->llist.head;
}

void *queue_peek(queue_t *queue_t) { return queue_t->front->data; }

void  queue_clear(queue_t *queue_t)
{
    while (queue_t->front != NULL) {
        queue_deque(queue_t);
    }
}
