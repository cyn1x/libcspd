#include "cspd_stack.test.h"
#include <assert.h>
#include <cspd_print.h>
#include <cspd_stack.h>
#include <cspd_types.h>

cspd_stack stack_setup(void)
{
    cspd_stack stack;
    cspd_stack_init(&stack, sizeof(int32));

    return stack;
}

void cspd_stack_test(void)
{
    cspd_stack stack = stack_setup();

    int        a     = 1;
    int        b     = 4;
    int        c     = 7;
    int        d     = 9;
    int        e     = 2;

    cspd_stack_push(&stack, &a);
    cspd_stack_push(&stack, &b);
    cspd_stack_push(&stack, &c);
    cspd_stack_push(&stack, &d);
    cspd_stack_push(&stack, &e);

    {
        void *data = cspd_stack_peek(&stack);
        assert(*(int32 *)data == 2);
    }

    {
        cspd_stack_pop(&stack);
        assert(*(int32 *)stack.top->data == 9);
    }

    cspd_stack_clear(&stack);
}
