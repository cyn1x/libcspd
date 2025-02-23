#define LIBCSPD_EXPORTS

#include "stack.h"
#include "linked_list.h"
#include <stdlib.h>

static void update_pointers(stack_t *stack_t);

void        stack_init(stack_t *stack_t, size_t data_size)
{
    llist_t llist;
    llist_init(&llist, data_size);

    stack_t->llist = llist;
}

void stack_push(stack_t *stack_t, void *data)
{
    llist_prepend(&stack_t->llist, data);
    update_pointers(stack_t);
}

void stack_pop(stack_t *stack_t)
{
    lnode_t *tmp = stack_t->top->next;

    free(stack_t->top->data);
    free(stack_t->top);

    stack_t->llist.head = tmp;

    update_pointers(stack_t);
}

void *stack_peek(stack_t *stack_t) { return stack_t->top->data; }

void  stack_clear(stack_t *stack_t)
{
    while (stack_t->top != NULL) {
        stack_pop(stack_t);
    }
}

static void update_pointers(stack_t *stack_t)
{
    if (stack_t->llist.head == stack_t->llist.tail) {
        stack_t->bottom = stack_t->llist.tail;
    }
    stack_t->top = stack_t->llist.head;
}
