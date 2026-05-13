#define LIBCSPD_EXPORTS

#include "cspd_stack.h"
#include "cspd_linked_list.h"
#include <stdlib.h>

static void update_pointers(cspd_stack *stack_t);

void        cspd_stack_init(cspd_stack *stack_t, size_t data_size)
{
    cspd_llist llist;
    cspd_llist_init(&llist, data_size);

    stack_t->llist = llist;
}

void cspd_stack_push(cspd_stack *stack_t, void *data)
{
    cspd_llist_prepend(&stack_t->llist, data);
    update_pointers(stack_t);
}

void cspd_stack_pop(cspd_stack *stack_t)
{
    cspd_llnode *tmp = stack_t->top->next;

    free(stack_t->top->data);
    free(stack_t->top);

    stack_t->llist.head = tmp;

    update_pointers(stack_t);
}

void *cspd_stack_peek(cspd_stack *stack_t)
{
    return stack_t->top->data;
}

void cspd_stack_clear(cspd_stack *stack_t)
{
    while (stack_t->top != NULL) {
        cspd_stack_pop(stack_t);
    }
}

static void update_pointers(cspd_stack *stack_t)
{
    if (stack_t->llist.head == stack_t->llist.tail) {
        stack_t->bottom = stack_t->llist.tail;
    }
    stack_t->top = stack_t->llist.head;
}
