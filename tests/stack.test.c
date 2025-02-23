#include "stack.test.h"
#include <assert.h>
#include <print.h>
#include <stack.h>
#include <types.h>

stack_t stack_setup(void)
{
    stack_t stack_t;
    stack_init(&stack_t, sizeof(int32));

    return stack_t;
}

void stack_test(void)
{
    stack_t stack_t = stack_setup();

    int     a       = 1;
    int     b       = 4;
    int     c       = 7;
    int     d       = 9;
    int     e       = 2;

    stack_push(&stack_t, &a);
    stack_push(&stack_t, &b);
    stack_push(&stack_t, &c);
    stack_push(&stack_t, &d);
    stack_push(&stack_t, &e);

    {
        void *data = stack_peek(&stack_t);
        assert(*(int32 *)data == 2);
    }

    {
        stack_pop(&stack_t);
        assert(*(int32 *)stack_t.top->data == 9);
    }

    stack_clear(&stack_t);
}
