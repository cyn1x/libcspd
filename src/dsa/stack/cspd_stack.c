#define CSPD_EXPORTS

#include "cspd_stack.h"
#include "cspd_mem.h"

static void update_pointers(cspd_stack *stack);

void cspd_stack_init(cspd_stack *stack, usize data_size)
{
    cspd_list_init(&stack->list, data_size);
    stack->top    = NULL;
    stack->bottom = NULL;
}

void cspd_stack_push(cspd_stack *stack, void *data)
{
    cspd_list_prepend(&stack->list, data);

    if (stack->list.head == stack->list.tail) {
        stack->bottom = stack->list.tail;
    }
    stack->top = stack->list.head;
}

void cspd_stack_pop(cspd_stack *stack)
{
    cspd_lnode *tmp = stack->top->next;

    cspd_free(stack->top->data);
    cspd_free(stack->top);

    stack->list.head = tmp;

    if (stack->list.head == stack->list.tail) {
        stack->bottom = stack->list.tail;
    }
    stack->top = stack->list.head;
}

void *cspd_stack_peek(cspd_stack *stack)
{
    return stack->top->data;
}

void cspd_stack_clear(cspd_stack *stack)
{
    while (stack->top != NULL) {
        cspd_stack_pop(stack);
    }
}
