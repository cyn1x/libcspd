#define LIBCSPD_EXPORTS

#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

static lnode_t *node_init(size_t data_size);
static lnode_t *partition(llist_t *llist_t, lnode_t *lo, lnode_t *hi);
static void     delete_node(llist_t *llist_t, lnode_t *node);

void            llist_init(llist_t *llist_t, size_t data_size)
{
    llist_t->data_size = data_size;

    llist_t->head      = NULL;
    llist_t->tail      = NULL;
}

lnode_t *node_init(size_t data_size)
{
    lnode_t *node = malloc(sizeof(lnode_t));

    node->data    = malloc(data_size);
    node->prev    = NULL;
    node->next    = NULL;

    return node;
}

void llist_append(llist_t *llist_t, void *data)
{
    lnode_t *node = node_init(llist_t->data_size);
    lnode_t *curr = llist_t->head;

    memcpy(node->data, data, llist_t->data_size);

    if (llist_t->head == NULL) {
        llist_t->head = node;
        llist_t->tail = llist_t->head;

        return;
    }

    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = llist_t->tail = node;
    llist_t->tail->prev        = curr;
}

void llist_prepend(llist_t *llist_t, void *data)
{
    lnode_t *node = node_init(llist_t->data_size);

    memcpy(node->data, data, llist_t->data_size);

    if (llist_t->head == NULL) {
        llist_t->head = node;
        llist_t->tail = llist_t->head;

        return;
    }

    lnode_t *temp = llist_t->head;
    if (llist_t->head->next != NULL) {
        llist_t->head->prev = node;
        llist_t->head       = llist_t->head->next;
    }

    node->next    = temp;
    llist_t->head = node;
}

void llist_insert(llist_t *llist_t, void *data, size_t idx)
{
    lnode_t *node = node_init(llist_t->data_size);
    lnode_t *curr = llist_t->head;

    memcpy(node->data, data, llist_t->data_size);

    if (idx == 0) {
        node->next    = llist_t->head;
        llist_t->head = node;

        return;
    }

    for (size_t i = 0; i < idx; i++) {
        if (curr->next == NULL) {
            // TODO: handle out of bounds

            return;
        }
        curr = curr->next;
    }

    lnode_t *temp = curr->prev;
    temp->next    = node;
    node->prev    = temp;
    curr->prev    = node;
    node->next    = curr;
}

void llist_move(llist_t *llist_t, lnode_t *node, lnode_t *dst, lnode_t *dst_ptr)
{
    if (node == dst) {
        // TODO: handle same node and target

        return;
    }

    if (dst->next != dst_ptr && dst->prev != dst_ptr) {
        // TODO: handle incorrect pointer args

        return;
    }

    bool adjacent = dst->prev == node || dst->next == node;
    if (adjacent) {
        llist_swap(llist_t, node, dst);

        return;
    }

    if (node == llist_t->head) {
        llist_t->head    = node->next;
        node->next->prev = NULL;
    } else if (node == llist_t->tail) {
        llist_t->tail    = node->prev;
        node->prev->next = NULL;
    } else {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }

    if (dst == llist_t->head && dst_ptr == NULL) {
        llist_t->head = node;
    } else if (dst == llist_t->tail && dst_ptr == NULL) {
        llist_t->tail = node;
    }

    if (dst->next == dst_ptr) {
        if (dst_ptr != NULL) {
            dst_ptr->prev = node;
        }
        node->next = dst_ptr;
        node->prev = dst;
        dst->next  = node;
    } else if (dst->prev == dst_ptr) {
        if (dst_ptr != NULL) {
            dst_ptr->next = node;
        }
        node->next = dst;
        node->prev = dst_ptr;
        dst->prev  = node;
    }
}

void llist_swap(llist_t *llist_t, lnode_t *a, lnode_t *b)
{
    if (a->next == b || b->next == a) {

        if (a->prev == b) {
            llist_swap(llist_t, b, a);
            return;
        }

        lnode_t *a_prev = a->prev;
        lnode_t *b_next = b->next;

        if (a_prev) {
            a_prev->next = b;
        }
        if (b_next) {
            b_next->prev = a;
        }

        a->prev = b;
        a->next = b_next;

        b->prev = a_prev;
        b->next = a;

    } else {

        lnode_t *a_prev = a->prev;
        lnode_t *a_next = a->next;

        if (a->prev) {
            a->prev->next = b;
        }
        if (a->next) {
            a->next->prev = b;
        }
        if (b->prev) {
            b->prev->next = a;
        }
        if (b->next) {
            b->next->prev = a;
        }

        a->prev = b->prev;
        a->next = b->next;
        b->prev = a_prev;
        b->next = a_next;
    }

    if (a == llist_t->head) {
        llist_t->head = b;
    } else if (b == llist_t->head) {
        llist_t->head = a;
    }

    if (a == llist_t->tail) {
        llist_t->tail = b;
    } else if (b == llist_t->tail) {
        llist_t->tail = a;
    }
}

void llist_delete(llist_t *llist_t, const void *key)
{
    lnode_t *curr = llist_t->head;

    while (curr != NULL) {
        int exists = memcmp(curr->data, key, llist_t->data_size);

        if (exists == 0) {
            delete_node(llist_t, curr);

            return;
        }

        curr = curr->next;
    }
}

void llist_erase(llist_t *llist_t, lnode_t *start, lnode_t *end)
{
    while (start != end) {
        lnode_t *temp = start->next;
        delete_node(llist_t, start);
        start = temp;
    }
}

void llist_clear(llist_t *llist_t)
{
    lnode_t *curr = llist_t->head;

    while (curr != NULL) {
        lnode_t *temp = curr->next;
        delete_node(llist_t, curr);
        curr = temp;
    }

    llist_t->data_size = 0;
    llist_t->head      = NULL;
    llist_t->tail      = NULL;
}

void llist_copy(llist_t *dst, llist_t *src)
{
    lnode_t *curr = src->head;
    lnode_t *temp = {0};

    while (curr != NULL) {
        lnode_t *node = node_init(dst->data_size);

        if (dst->head == NULL) {
            dst->head = node;
        }
        dst->tail = node;

        memcpy(node->data, curr->data, dst->data_size);

        curr = curr->next;

        // hold ptr ref to previous node to assign its next and prev pointers
        if (temp != NULL) {
            temp->next = node;
            node->prev = temp;
        }
        temp = node;
    }
}

void llist_reverse(llist_t *llist_t)
{
    lnode_t *curr = llist_t->head;

    if (curr == NULL) {
        // TODO: handle empty list

        return;
    }

    while (curr != NULL) {
        lnode_t *temp = curr->next;
        curr->next    = curr->prev;
        curr->prev    = temp;
        curr          = temp;
    }

    // swap head and tail pointers
    lnode_t *head = llist_t->head;
    llist_t->head = llist_t->tail;
    llist_t->tail = head;
}

lnode_t *llist_find(llist_t *llist_t, const void *key)
{
    lnode_t *node = llist_lsearch(llist_t, key);

    return node;
}

size_t llist_index(llist_t *llist_t, lnode_t *node)
{
    size_t   idx  = 0;
    lnode_t *curr = llist_t->head;
    while (curr && curr != node) {
        idx++;
        curr = curr->next;
    }

    return idx;
}

lnode_t *llist_lsearch(llist_t *llist_t, const void *key)
{
    lnode_t *curr = llist_t->head;

    while (curr != NULL) {
        int exists = memcmp(curr->data, key, llist_t->data_size);

        if (exists == 0) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

void llist_bsort(llist_t *llist_t)
{
    lnode_t *a = llist_t->head;
    while (a) {

        lnode_t *b = llist_t->head;
        while (b) {
            if (llist_t->_cmp(a->data, b->data) != 1) {
                void *tmp = a->data;
                a->data   = b->data;
                b->data   = tmp;
            }
            b = b->next;
        }
        a = a->next;
    }
}

void llist_qsort(llist_t *llist_t, lnode_t *lo, lnode_t *hi)
{
    if (!lo || !hi || lo->prev == hi) {
        return;
    }

    lnode_t *pvt = partition(llist_t, lo, hi);

    llist_qsort(llist_t, lo, pvt->prev);
    llist_qsort(llist_t, pvt->next, hi);
}

static lnode_t *partition(llist_t *llist_t, lnode_t *lo, lnode_t *hi)
{
    lnode_t *pvt  = hi;
    lnode_t *curr = lo;
    lnode_t *idx  = lo;
    void    *tmp;

    while (curr != NULL) {
        int cmp = llist_t->_cmp(curr->data, pvt->data);

        if (cmp == -1) {
            tmp        = idx->data;
            idx->data  = curr->data;
            curr->data = tmp;
            idx        = idx->next;
            curr       = curr->next;
        } else {
            curr = curr->next;
        }
    }

    tmp       = idx->data;
    idx->data = pvt->data;
    pvt->data = tmp;

    return idx;
}

void delete_node(llist_t *llist_t, lnode_t *node)
{
    lnode_t *prev = node->prev;
    lnode_t *next = node->next;

    if (node->prev != NULL) {
        prev->next = next;
    } else {
        llist_t->head = next;
    }
    if (node->next != NULL) {
        next->prev = prev;
    } else {
        llist_t->tail = prev;
    }

    free(node->data);
    node->next = NULL;
    node->prev = NULL;
    free(node);
}
