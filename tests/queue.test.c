#include "queue.test.h"
#include "types.h"
#include <print.h>
#include <stdio.h>

void print_data(void *data)
{
    printf("{ ");
    print(*(int32 *)data, " ");
    printf("} \n");
}

queue queue_setup(void)
{
    queue queue;
    queue_init(&queue, sizeof(int32));

    return queue;
}

void queue_test(void)
{
    queue queue = queue_setup();

    int   a     = 1;
    int   b     = 4;
    int   c     = 7;
    int   d     = 9;
    int   e     = 2;

    queue_enqueue(&queue, &a);
    queue_enqueue(&queue, &b);
    queue_enqueue(&queue, &c);
    queue_enqueue(&queue, &d);
    queue_enqueue(&queue, &e);

    {
        void *data = queue_peek(&queue);
        // print_data(data);
        // Output: { 1 }
        assert(*(int32 *)data == 1);
    }

    {
        queue_deque(&queue);
        assert(*(int32 *)queue.front->data == 4);
    }

    queue_clear(&queue);
}
