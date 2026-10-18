#include "cspd_dsa.test.h"
#include <assert.h>
#include <cspd_print.h>
#include <cspd_stack.h>
#include <cspd_types.h>

cspd_stack stack_setup(void)
{
    //! [Initialize]
    cspd_stack stack;
    cspd_stack_init(&stack, sizeof(i32));

    return stack;
    //! [Initialize]
}

void cspd_stack_test(void)
{
    cspd_stack stack = stack_setup();

    //! [Push]
    int        a = 1;
    int        b = 4;
    int        c = 7;
    int        d = 9;
    int        e = 2;

    cspd_stack_push(&stack, &a);
    cspd_stack_push(&stack, &b);
    cspd_stack_push(&stack, &c);
    cspd_stack_push(&stack, &d);
    cspd_stack_push(&stack, &e);
    //! [Push]

    {
        //! [Peek]
        void *data = cspd_stack_peek(&stack);
        assert(*(i32 *)data == 2);
        //! [Peek]
    }

    {
        //! [Pop]
        cspd_stack_pop(&stack);
        assert(*(i32 *)stack.top->data == 9);
        //! [Pop]
    }

    cspd_stack_clear(&stack);
}
