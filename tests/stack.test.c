#include "stack.test.h"
#include "types.h"
#include <print.h>
#include <stdio.h>

static void print_data(void *data)
{
    printf("{ ");
    print(*(int32 *)data, " ");
    printf("} \n");
}

stack stack_setup(void)
{
    stack stack;
    stack_init(&stack, sizeof(int32));

    return stack;
}

void stack_test(void)
{
    stack stack = stack_setup();

    int   a     = 1;
    int   b     = 4;
    int   c     = 7;
    int   d     = 9;
    int   e     = 2;

    stack_push(&stack, &a);
    stack_push(&stack, &b);
    stack_push(&stack, &c);
    stack_push(&stack, &d);
    stack_push(&stack, &e);

    {
        void *data = stack_peek(&stack);
        // print_data(data);
        // Output: { 1 }
        assert(*(int32 *)data == 2);
    }

    {
        stack_pop(&stack);
        assert(*(int32 *)stack.top->data == 9);
    }

    stack_clear(&stack);
}
