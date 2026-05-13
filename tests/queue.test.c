#include "queue.test.h"
#include <assert.h>
#include <cspd_print.h>
#include <queue.h>
#include <cspd_types.h>

cspd_queue queue_setup(void)
{
    cspd_queue queue;
    cspd_queue_init(&queue, sizeof(int32));

    return queue;
}

void cspd_queue_test(void)
{
    cspd_queue queue = queue_setup();

    int        a     = 1;
    int        b     = 4;
    int        c     = 7;
    int        d     = 9;
    int        e     = 2;

    cspd_queue_enqueue(&queue, &a);
    cspd_queue_enqueue(&queue, &b);
    cspd_queue_enqueue(&queue, &c);
    cspd_queue_enqueue(&queue, &d);
    cspd_queue_enqueue(&queue, &e);

    {
        void *data = cspd_queue_peek(&queue);
        assert(*(int32 *)data == 1);
    }

    {
        cspd_queue_deque(&queue);
        assert(*(int32 *)queue.front->data == 4);
    }

    cspd_queue_clear(&queue);
}
