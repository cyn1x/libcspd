#define LIBCSPD_EXPORTS

#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

static llnode_t *node_init(size_t data_size);
static llnode_t *partition(llist_t *llist, llnode_t *lo, llnode_t *hi);
static void      delete_node(llist_t *llist, llnode_t *node);

void             llist_init(llist_t *llist, size_t data_size)
{
    llist->data_size = data_size;

    llist->head      = NULL;
    llist->tail      = NULL;
}

llnode_t *node_init(size_t data_size)
{
    llnode_t *node = malloc(sizeof(llnode_t));

    node->data     = malloc(data_size);
    node->prev     = NULL;
    node->next     = NULL;

    return node;
}

void llist_append(llist_t *llist, void *data)
{
    llnode_t *node = node_init(llist->data_size);
    llnode_t *curr = llist->head;

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

void llist_prepend(llist_t *llist, void *data)
{
    llnode_t *node = node_init(llist->data_size);

    memcpy(node->data, data, llist->data_size);

    if (llist->head == NULL) {
        llist->head = node;
        llist->tail = llist->head;

        return;
    }

    llnode_t *temp = llist->head;
    if (llist->head->next != NULL) {
        llist->head->prev = node;
        llist->head       = llist->head->next;
    }

    node->next  = temp;
    llist->head = node;
}

void llist_insert(llist_t *llist, void *data, size_t idx)
{
    llnode_t *node = node_init(llist->data_size);
    llnode_t *curr = llist->head;

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

    llnode_t *temp = curr->prev;
    temp->next     = node;
    node->prev     = temp;
    curr->prev     = node;
    node->next     = curr;
}

void llist_move(llist_t *llist, llnode_t *node, llnode_t *dst,
                llnode_t *dst_ptr)
{
    if (node == dst) {
        // TODO: handle same node and target

        return;
    }

    // Check if the destination pointer actually belongs to the destination
    // node's next or prev pointers
    if (dst->next != dst_ptr && dst->prev != dst_ptr) {
        // TODO: handle incorrect pointer args

        return;
    }

    bool adjacent = dst->prev == node || dst->next == node;
    if (adjacent) {
        llist_swap(llist, node, dst);

        return;
    }

    // Handle case where the node to move is either the head or tail
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

    // Handle case where the destination node is the head or tail
    if (dst == llist->head && dst_ptr == NULL) {
        llist->head = node;
    } else if (dst == llist->tail && dst_ptr == NULL) {
        llist->tail = node;
    }

    // Expected case
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

void llist_swap(llist_t *llist, llnode_t *a, llnode_t *b)
{
    if (a->next == b || b->next == a) {
        // Handle swapping adjacent nodes

        if (a->prev == b) {
            // The order of operations is important here. The pointer to `a`
            // must always precede `b` in the linked list since the `next` and
            // `prev` pointers for `a` are changed first.
            llist_swap(llist, b, a);
            return;
        }

        llnode_t *a_prev = a->prev;
        llnode_t *b_next = b->next;

        if (a_prev) {
            a_prev->next = b;
        }
        if (b_next) {
            b_next->prev = a;
        }

        // Change the `next` and `prev` pointers for a first
        a->prev = b;
        a->next = b_next;

        b->prev = a_prev;
        b->next = a;

    } else {
        // Nodes are not adjacent

        llnode_t *a_prev = a->prev;
        llnode_t *a_next = a->next;

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

void llist_delete(llist_t *llist, const void *key)
{
    llnode_t *curr = llist->head;

    while (curr != NULL) {
        int exists = memcmp(curr->data, key, llist->data_size);

        if (exists == 0) {
            delete_node(llist, curr);

            return;
        }

        curr = curr->next;
    }
}

void llist_erase(llist_t *llist, llnode_t *start, llnode_t *end)
{
    while (start != end) {
        llnode_t *temp = start->next;
        delete_node(llist, start);
        start = temp;
    }
}

void llist_clear(llist_t *llist)
{
    llnode_t *curr = llist->head;

    while (curr != NULL) {
        llnode_t *temp = curr->next;
        delete_node(llist, curr);
        curr = temp;
    }

    llist->head = NULL;
    llist->tail = NULL;
}

void llist_copy(llist_t *dst, llist_t *src)
{
    llnode_t *curr = src->head;
    llnode_t *temp = {0};

    if (dst->head != NULL) {
        llist_clear(dst);
    }

    while (curr != NULL) {
        llnode_t *node = node_init(dst->data_size);

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

void llist_reverse(llist_t *llist)
{
    llnode_t *curr = llist->head;

    if (curr == NULL) {
        // TODO: handle empty list

        return;
    }

    while (curr != NULL) {
        llnode_t *temp = curr->next;
        curr->next     = curr->prev;
        curr->prev     = temp;
        curr           = temp;
    }

    // swap head and tail pointers
    llnode_t *head = llist->head;
    llist->head    = llist->tail;
    llist->tail    = head;
}

llnode_t *llist_find(llist_t *llist, const void *key)
{
    llnode_t *node = llist_lsearch(llist, key);

    return node;
}

size_t llist_index(llist_t *llist, llnode_t *node)
{
    size_t    idx  = 0;
    llnode_t *curr = llist->head;
    while (curr && curr != node) {
        idx++;
        curr = curr->next;
    }

    return idx;
}

llnode_t *llist_lsearch(llist_t *llist, const void *key)
{
    llnode_t *curr = llist->head;

    while (curr != NULL) {
        int exists = memcmp(curr->data, key, llist->data_size);

        if (exists == 0) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

void llist_bsort(llist_t *llist)
{
    llnode_t *a = llist->head;
    while (a) {

        llnode_t *b = llist->head;
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

void llist_qsort(llist_t *llist, llnode_t *lo, llnode_t *hi)
{
    if (!lo || !hi || lo->prev == hi) {
        return;
    }

    llnode_t *pvt = partition(llist, lo, hi);

    llist_qsort(llist, lo, pvt->prev);
    llist_qsort(llist, pvt->next, hi);
}

static llnode_t *partition(llist_t *llist, llnode_t *lo, llnode_t *hi)
{
    llnode_t *pvt  = hi;
    llnode_t *curr = lo;
    llnode_t *idx  = lo;
    void     *tmp;

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

void delete_node(llist_t *llist, llnode_t *node)
{
    llnode_t *prev = node->prev;
    llnode_t *next = node->next;

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
