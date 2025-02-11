#define LIBCSPD_EXPORTS

#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

static lnode_t *node_init(size_t data_size);
static lnode_t *partition(llist *llist, lnode_t *lo, lnode_t *hi);
static void     delete_node(llist *llist, lnode_t *node);

void            llist_init(llist *llist, size_t data_size)
{
    llist->data_size = data_size;

    llist->head      = NULL;
    llist->tail      = NULL;
}

lnode_t *node_init(size_t data_size)
{
    lnode_t *node = malloc(sizeof(lnode_t));

    node->data    = malloc(sizeof(data_size));
    node->prev    = NULL;
    node->next    = NULL;

    return node;
}

void llist_append(llist *llist, void *data)
{
    lnode_t *node = node_init(llist->data_size);
    lnode_t *curr = llist->head;

    memcpy(node->data, data, llist->data_size);

    if (llist->head == NULL) {
        llist->head = node;
        llist->tail = llist->head;

        return;
    }

    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = llist->tail = node;
    llist->tail->prev        = curr;
}

void llist_prepend(llist *llist, void *data)
{
    lnode_t *node = node_init(llist->data_size);

    memcpy(node->data, data, llist->data_size);

    if (llist->head == NULL) {
        llist->head = node;
        llist->tail = llist->head;

        return;
    }

    lnode_t *temp = llist->head;
    if (llist->head->next != NULL) {
        llist->head->prev = node;
        llist->head       = llist->head->next;
    }

    node->next  = temp;
    llist->head = node;
}

void llist_insert(llist *llist, void *data, size_t idx)
{
    lnode_t *node = node_init(llist->data_size);
    lnode_t *curr = llist->head;

    memcpy(node->data, data, llist->data_size);

    if (idx == 0) {
        node->next  = llist->head;
        llist->head = node;

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

void llist_move(llist *llist, lnode_t *node, lnode_t *dst, lnode_t *dst_ptr)
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
        llist_swap(llist, node, dst);

        return;
    }

    if (node == llist->head) {
        llist->head      = node->next;
        node->next->prev = NULL;
    } else if (node == llist->tail) {
        llist->tail      = node->prev;
        node->prev->next = NULL;
    } else {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }

    if (dst == llist->head && dst_ptr == NULL) {
        llist->head = node;
    } else if (dst == llist->tail && dst_ptr == NULL) {
        llist->tail = node;
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

void llist_swap(llist *llist, lnode_t *a, lnode_t *b)
{
    if (a->next == b || b->next == a) {

        if (a->prev == b) {
            llist_swap(llist, b, a);
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

    if (a == llist->head) {
        llist->head = b;
    } else if (b == llist->head) {
        llist->head = a;
    }

    if (a == llist->tail) {
        llist->tail = b;
    } else if (b == llist->tail) {
        llist->tail = a;
    }
}

void llist_delete(llist *llist, const void *key)
{
    lnode_t *curr = llist->head;

    while (curr != NULL) {
        int exists = memcmp(curr->data, key, llist->data_size);

        if (exists == 0) {
            delete_node(llist, curr);

            return;
        }

        curr = curr->next;
    }
}

void llist_erase(llist *llist, lnode_t *start, lnode_t *end)
{
    while (start != end) {
        lnode_t *temp = start->next;
        delete_node(llist, start);
        start = temp;
    }
}

void llist_clear(llist *llist)
{
    lnode_t *curr = llist->head;

    while (curr != NULL) {
        lnode_t *temp = curr->next;
        delete_node(llist, curr);
        curr = temp;
    }

    llist->data_size = 0;
    llist->head      = NULL;
    llist->tail      = NULL;
}

void llist_copy(llist *dst, llist *src)
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

void llist_reverse(llist *llist)
{
    lnode_t *curr = llist->head;

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
    lnode_t *head = llist->head;
    llist->head   = llist->tail;
    llist->tail   = head;
}

lnode_t *llist_find(llist *llist, const void *key)
{
    lnode_t *node = llist_lsearch(llist, key);

    return node;
}

size_t llist_index(llist *llist, lnode_t *node)
{
    size_t   idx  = 0;
    lnode_t *curr = llist->head;
    while (curr && curr != node) {
        idx++;
        curr = curr->next;
    }

    return idx;
}

lnode_t *llist_lsearch(llist *llist, const void *key)
{
    lnode_t *curr = llist->head;

    while (curr != NULL) {
        int exists = memcmp(curr->data, key, llist->data_size);

        if (exists == 0) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

void llist_bsort(llist *llist)
{
    lnode_t *a = llist->head;
    while (a) {

        lnode_t *b = llist->head;
        while (b) {
            if (llist->_cmp(a->data, b->data) != 1) {
                void *tmp = a->data;
                a->data   = b->data;
                b->data   = tmp;
            }
            b = b->next;
        }
        a = a->next;
    }
}

void llist_qsort(llist *llist, lnode_t *lo, lnode_t *hi)
{
    if (!lo || !hi || lo->prev == hi) {
        return;
    }

    lnode_t *pvt = partition(llist, lo, hi);

    llist_qsort(llist, lo, pvt->prev);
    llist_qsort(llist, pvt->next, hi);
}

static lnode_t *partition(llist *llist, lnode_t *lo, lnode_t *hi)
{
    lnode_t *pvt  = hi;
    lnode_t *curr = lo;
    lnode_t *idx  = lo;
    void    *tmp;

    while (curr != NULL) {
        int cmp = llist->_cmp(curr->data, pvt->data);

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

void delete_node(llist *llist, lnode_t *node)
{
    lnode_t *prev = node->prev;
    lnode_t *next = node->next;

    if (node->prev != NULL) {
        prev->next = next;
    } else {
        llist->head = next;
    }
    if (node->next != NULL) {
        next->prev = prev;
    } else {
        llist->tail = prev;
    }

    free(node->data);
    node->next = NULL;
    node->prev = NULL;
    free(node);
}
