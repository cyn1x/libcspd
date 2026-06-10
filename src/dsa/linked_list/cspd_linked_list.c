#define CSPD_EXPORTS

#include "cspd_linked_list.h"
#include "cspd_mem.h"
#include <stdbool.h>

static cspd_llnode *node_init(size_t data_size);
static cspd_llnode *partition(cspd_llist *llist, cspd_llnode *lo,
                              cspd_llnode *hi);
static void         delete_node(cspd_llist *llist, cspd_llnode *node);

void                cspd_llist_init(cspd_llist *llist, size_t data_size)
{
    llist->data_size = data_size;

    llist->head      = NULL;
    llist->tail      = NULL;
}

cspd_llnode *node_init(size_t data_size)
{
    cspd_llnode *node = cspd_malloc(sizeof(cspd_llnode));

    node->data        = cspd_malloc(data_size);
    node->prev        = NULL;
    node->next        = NULL;

    return node;
}

void cspd_llist_append(cspd_llist *llist, void *data)
{
    cspd_llnode *node = node_init(llist->data_size);
    cspd_llnode *curr = llist->head;

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

void cspd_llist_prepend(cspd_llist *llist, void *data)
{
    cspd_llnode *node = node_init(llist->data_size);

    memcpy(node->data, data, llist->data_size);

    if (llist->head == NULL) {
        llist->head = node;
        llist->tail = llist->head;

        return;
    }

    cspd_llnode *temp = llist->head;
    if (llist->head->next != NULL) {
        llist->head->prev = node;
        llist->head       = llist->head->next;
    }

    node->next  = temp;
    llist->head = node;
}

void cspd_llist_insert(cspd_llist *llist, void *data, size_t idx)
{
    cspd_llnode *node = node_init(llist->data_size);
    cspd_llnode *curr = llist->head;

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

    cspd_llnode *temp = curr->prev;
    temp->next        = node;
    node->prev        = temp;
    curr->prev        = node;
    node->next        = curr;
}

void cspd_llist_move(cspd_llist *llist, cspd_llnode *node, cspd_llnode *dst,
                     cspd_llnode *dst_ptr)
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
        cspd_llist_swap(llist, node, dst);

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

void cspd_llist_swap(cspd_llist *llist, cspd_llnode *a, cspd_llnode *b)
{
    if (a->next == b || b->next == a) {
        // Handle swapping adjacent nodes

        if (a->prev == b) {
            // The order of operations is important here. The pointer to `a`
            // must always precede `b` in the linked list since the `next` and
            // `prev` pointers for `a` are changed first.
            cspd_llist_swap(llist, b, a);
            return;
        }

        cspd_llnode *a_prev = a->prev;
        cspd_llnode *b_next = b->next;

        if (a_prev) {
            a_prev->next = b;
        }
        if (b_next) {
            b_next->prev = a;
        }

        // Change the `next` and `prev` pointers for `a` first
        a->prev = b;
        a->next = b_next;

        b->prev = a_prev;
        b->next = a;

    } else {
        // Nodes are not adjacent

        cspd_llnode *a_prev = a->prev;
        cspd_llnode *a_next = a->next;

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

void cspd_llist_delete(cspd_llist *llist, const void *key)
{
    cspd_llnode *curr = llist->head;

    while (curr != NULL) {
        int exists = memcmp(curr->data, key, llist->data_size);

        if (exists == 0) {
            delete_node(llist, curr);

            return;
        }

        curr = curr->next;
    }
}

void cspd_llist_erase(cspd_llist *llist, cspd_llnode *start, cspd_llnode *end)
{
    while (start != end) {
        cspd_llnode *temp = start->next;
        delete_node(llist, start);
        start = temp;
    }
}

void cspd_llist_clear(cspd_llist *llist)
{
    cspd_llnode *curr = llist->head;

    while (curr != NULL) {
        cspd_llnode *temp = curr->next;
        delete_node(llist, curr);
        curr = temp;
    }

    llist->head = NULL;
    llist->tail = NULL;
}

void cspd_llist_copy(cspd_llist *dst, cspd_llist *src)
{
    cspd_llnode *curr = src->head;
    cspd_llnode *temp = {0};

    // TODO: Handle different data sizes

    if (dst->head != NULL) {
        cspd_llist_clear(dst);
    }

    while (curr != NULL) {
        cspd_llnode *node = node_init(dst->data_size);

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

void cspd_llist_reverse(cspd_llist *llist)
{
    cspd_llnode *curr = llist->head;

    if (curr == NULL) {
        // TODO: handle empty list

        return;
    }

    while (curr != NULL) {
        cspd_llnode *temp = curr->next;
        curr->next        = curr->prev;
        curr->prev        = temp;
        curr              = temp;
    }

    // swap head and tail pointers
    cspd_llnode *head = llist->head;
    llist->head       = llist->tail;
    llist->tail       = head;
}

cspd_llnode *cspd_llist_find(cspd_llist *llist, const void *key)
{
    cspd_llnode *node = cspd_llist_lsearch(llist, key);

    return node;
}

size_t cspd_llist_index(cspd_llist *llist, cspd_llnode *node)
{
    size_t       idx  = 0;
    cspd_llnode *curr = llist->head;
    while (curr && curr != node) {
        idx++;
        curr = curr->next;
    }

    return idx;
}

cspd_llnode *cspd_llist_lsearch(cspd_llist *llist, const void *key)
{
    cspd_llnode *curr = llist->head;

    while (curr != NULL) {
        int exists = memcmp(curr->data, key, llist->data_size);

        if (exists == 0) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

void cspd_llist_bsort(cspd_llist *llist)
{
    cspd_llnode *a = llist->head;
    while (a) {

        cspd_llnode *b = llist->head;
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

void cspd_llist_qsort(cspd_llist *llist, cspd_llnode *lo, cspd_llnode *hi)
{
    if (!lo || !hi || lo->prev == hi) {
        return;
    }

    cspd_llnode *pvt = partition(llist, lo, hi);

    cspd_llist_qsort(llist, lo, pvt->prev);
    cspd_llist_qsort(llist, pvt->next, hi);
}

static cspd_llnode *partition(cspd_llist *llist, cspd_llnode *lo,
                              cspd_llnode *hi)
{
    cspd_llnode *pvt  = hi;
    cspd_llnode *curr = lo;
    cspd_llnode *idx  = lo;
    void        *tmp;

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

void delete_node(cspd_llist *llist, cspd_llnode *node)
{
    cspd_llnode *prev = node->prev;
    cspd_llnode *next = node->next;

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

    cspd_free(node->data);
    node->next = NULL;
    node->prev = NULL;
    cspd_free(node);
}
