#define LIBCSPD_EXPORTS

#include "stack.h"
#include "linked_list.h"
#include <stdlib.h>

static void update_pointers(stack *stack);

void        stack_init(stack *stack, size_t data_size)
{
    llist llist;
    llist_init(&llist, data_size);

    stack->llist = llist;
}

void stack_push(stack *stack, void *data)
{
    llist_prepend(&stack->llist, data);
    update_pointers(stack);
}

void stack_pop(stack *stack)
{
    lnode_t *tmp = stack->top->next;

    free(stack->top->data);
    free(stack->top);

    stack->llist.head = tmp;

    update_pointers(stack);
}

void *stack_peek(stack *stack) { return stack->top->data; }

void  stack_clear(stack *stack)
{
    while (stack->top != NULL) {
        stack_pop(stack);
    }
}

static void update_pointers(stack *stack)
{
    if (stack->llist.head == stack->llist.tail) {
        stack->bottom = stack->llist.tail;
    }
    stack->top = stack->llist.head;
}
