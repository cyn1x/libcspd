#define CSPD_EXPORTS

#include "cspd_stack.h"
#include "cspd_linked_list.h"
#include "cspd_mem.h"

static void update_pointers(cspd_stack *stack);

void        cspd_stack_init(cspd_stack *stack, size_t data_size)
{
    cspd_llist llist;
    cspd_llist_init(&llist, data_size);

    stack->llist = llist;
}

void cspd_stack_push(cspd_stack *stack, void *data)
{
    cspd_llist_prepend(&stack->llist, data);
    update_pointers(stack);
}

void cspd_stack_pop(cspd_stack *stack)
{
    cspd_llnode *tmp = stack->top->next;

    cspd_free(stack->top->data);
    cspd_free(stack->top);

    stack->llist.head = tmp;

    update_pointers(stack);
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

static void update_pointers(cspd_stack *stack)
{
    if (stack->llist.head == stack->llist.tail) {
        stack->bottom = stack->llist.tail;
    }
    stack->top = stack->llist.head;
}
