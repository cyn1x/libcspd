#include "queue.test.h"
#include <assert.h>
#include <print.h>
#include <queue.h>
#include <types.h>

queue_t queue_setup(void)
{
    queue_t queue_t;
    queue_init(&queue_t, sizeof(int32));

    return queue_t;
}

void queue_test(void)
{
    queue_t queue_t = queue_setup();

    int     a       = 1;
    int     b       = 4;
    int     c       = 7;
    int     d       = 9;
    int     e       = 2;

    queue_enqueue(&queue_t, &a);
    queue_enqueue(&queue_t, &b);
    queue_enqueue(&queue_t, &c);
    queue_enqueue(&queue_t, &d);
    queue_enqueue(&queue_t, &e);

    {
        void *data = queue_peek(&queue_t);
        assert(*(int32 *)data == 1);
    }

    {
        queue_deque(&queue_t);
        assert(*(int32 *)queue_t.front->data == 4);
    }

    queue_clear(&queue_t);
}
