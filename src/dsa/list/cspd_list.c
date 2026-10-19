#define CSPD_EXPORTS

#include "cspd_list.h"
#include "cspd_mem.h"

/**
 * @internal
 *
 * @brief Initializes a new node.
 *
 * Memory is allocated for the new node and the data that will reside within the
 * new node structure. The `prev` and `next` pointers are set to `NULL`.
 *
 * @param list Pointer to the linked list structure.
 *
 * @returns Pointer to the new node in memory.
 *
 * @b Example
 * @snippet cspd_linked_list.test.c Initialize
 */
static cspd_lnode *node_init(usize data_size);

/**
 * @internal
 *
 * @brief
 *
 *
 *
 * @param lo
 * @param hi
 * @param cmp Comparator function pointer.
 *
 * @returns
 */
static cspd_lnode *partition(cspd_lnode *lo, cspd_lnode *hi, cspd_cmp cmp);

/**
 * @internal
 *
 * @brief
 *
 *
 *
 * @param list Pointer to the linked list structure.
 * @param lnode Pointer to the linked list node.
 */
static void delete_node(cspd_list *list, cspd_lnode *node);

void cspd_list_init(cspd_list *list, usize data_size)
{
    list->data_size = data_size;

    list->head      = NULL;
    list->tail      = NULL;
}

void cspd_list_append(cspd_list *list, void *data)
{
    cspd_lnode *node = node_init(list->data_size);
    cspd_lnode *curr = list->head;

    memcpy(node->data, data, list->data_size);

    if (list->head == NULL) {
        list->head = node;
        list->tail = list->head;

        return;
    }

    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = list->tail = node;
    list->tail->prev        = curr;
}

void cspd_list_prepend(cspd_list *list, void *data)
{
    cspd_lnode *node = node_init(list->data_size);

    memcpy(node->data, data, list->data_size);

    if (list->head == NULL) {
        list->head = node;
        list->tail = list->head;

        return;
    }

    cspd_lnode *temp = list->head;
    if (list->head->next != NULL) {
        list->head->prev = node;
        list->head       = list->head->next;
    }

    node->next = temp;
    temp->prev = node;
    list->head = node;
}

void cspd_list_insert(cspd_list *list, void *data, usize idx)
{
    cspd_lnode *node = node_init(list->data_size);
    cspd_lnode *curr = list->head;

    memcpy(node->data, data, list->data_size);

    if (idx == 0) {
        node->next       = list->head;
        list->head->prev = node;
        list->head       = node;

        return;
    }

    for (usize i = 0; i < idx; i++) {
        if (curr->next == NULL) {
            // TODO: handle out of bounds

            return;
        }
        curr = curr->next;
    }

    cspd_lnode *temp = curr->prev;
    temp->next       = node;
    node->prev       = temp;
    curr->prev       = node;
    node->next       = curr;
}

void cspd_list_move(cspd_list *list, cspd_lnode *node, cspd_lnode *dst,
                    cspd_lnode *dst_ptr)
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
        cspd_list_swap(list, node, dst);

        return;
    }

    // Handle case where the node to move is either the head or tail
    if (node == list->head) {
        list->head       = node->next;
        node->next->prev = NULL;
    } else if (node == list->tail) {
        list->tail       = node->prev;
        node->prev->next = NULL;
    } else {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }

    // Handle case where the destination node is the head or tail
    if (dst == list->head && dst_ptr == NULL) {
        list->head = node;
    } else if (dst == list->tail && dst_ptr == NULL) {
        list->tail = node;
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

void cspd_list_swap(cspd_list *list, cspd_lnode *a, cspd_lnode *b)
{
    if (a->next == b || b->next == a) {
        // Handle swapping adjacent nodes

        if (a->prev == b) {
            // The order of operations is important here. The pointer to `a`
            // must always precede `b` in the linked list since the `next` and
            // `prev` pointers for `a` are changed first.
            cspd_list_swap(list, b, a);
            return;
        }

        cspd_lnode *a_prev = a->prev;
        cspd_lnode *b_next = b->next;

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

        cspd_lnode *a_prev = a->prev;
        cspd_lnode *a_next = a->next;

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

    if (a == list->head) {
        list->head = b;
    } else if (b == list->head) {
        list->head = a;
    }

    if (a == list->tail) {
        list->tail = b;
    } else if (b == list->tail) {
        list->tail = a;
    }
}

void cspd_list_delete(cspd_list *list, const void *key)
{
    cspd_lnode *curr = list->head;

    while (curr != NULL) {
        int exists = memcmp(curr->data, key, list->data_size);

        if (exists == 0) {
            delete_node(list, curr);

            return;
        }

        curr = curr->next;
    }
}

void cspd_list_erase(cspd_list *list, cspd_lnode *start, cspd_lnode *end)
{
    while (start != end) {
        cspd_lnode *temp = start->next;
        delete_node(list, start);
        start = temp;
    }
}

void cspd_list_clear(cspd_list *list)
{
    cspd_lnode *curr = list->head;

    while (curr != NULL) {
        cspd_lnode *temp = curr->next;
        delete_node(list, curr);
        curr = temp;
    }

    list->head = NULL;
    list->tail = NULL;
}

void cspd_list_copy(cspd_list *dst, cspd_list *src)
{
    cspd_lnode *curr = src->head;
    cspd_lnode *temp = {0};

    // TODO: Handle different data sizes

    if (dst->head != NULL) {
        cspd_list_clear(dst);
    }

    while (curr != NULL) {
        cspd_lnode *node = node_init(dst->data_size);

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

void cspd_list_reverse(cspd_list *list)
{
    cspd_lnode *curr = list->head;

    if (curr == NULL) {
        // TODO: handle empty list

        return;
    }

    while (curr != NULL) {
        cspd_lnode *temp = curr->next;
        curr->next       = curr->prev;
        curr->prev       = temp;
        curr             = temp;
    }

    // swap head and tail pointers
    cspd_lnode *head = list->head;
    list->head       = list->tail;
    list->tail       = head;
}

cspd_lnode *cspd_list_find(cspd_list *list, const void *key)
{
    cspd_lnode *node = cspd_list_lsearch(list, key);

    return node;
}

usize cspd_list_index(cspd_list *list, cspd_lnode *node)
{
    usize       idx  = 0;
    cspd_lnode *curr = list->head;
    while (curr && curr != node) {
        idx++;
        curr = curr->next;
    }

    return idx;
}

cspd_lnode *cspd_list_lsearch(cspd_list *list, const void *key)
{
    cspd_lnode *curr = list->head;

    while (curr != NULL) {
        int exists = memcmp(curr->data, key, list->data_size);

        if (exists == 0) {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

void cspd_list_bsort(cspd_list *list, cspd_cmp cmp)
{
    cspd_lnode *a = list->head;
    while (a) {

        cspd_lnode *b = list->head;
        while (b) {
            if (cmp(a->data, b->data) != 1) {
                void *tmp = a->data;
                a->data   = b->data;
                b->data   = tmp;
            }
            b = b->next;
        }
        a = a->next;
    }
}

void cspd_list_qsort(cspd_list *list, cspd_lnode *lo, cspd_lnode *hi,
                     cspd_cmp cmp)
{
    if (!lo || !hi || lo->prev == hi) {
        return;
    }

    cspd_lnode *pvt = partition(lo, hi, cmp);

    cspd_list_qsort(list, lo, pvt->prev, cmp);
    cspd_list_qsort(list, pvt->next, hi, cmp);
}

static cspd_lnode *node_init(usize data_size)
{
    cspd_lnode *node = cspd_malloc(sizeof(cspd_lnode));

    node->data       = cspd_malloc(data_size);
    node->prev       = NULL;
    node->next       = NULL;

    return node;
}

static cspd_lnode *partition(cspd_lnode *lo, cspd_lnode *hi, cspd_cmp cmp)
{
    cspd_lnode *pvt  = hi;
    cspd_lnode *curr = lo;
    cspd_lnode *idx  = lo;
    void       *tmp;

    while (curr != NULL) {
        int result = cmp(curr->data, pvt->data);

        if (result == -1) {
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

static void delete_node(cspd_list *list, cspd_lnode *node)
{
    cspd_lnode *prev = node->prev;
    cspd_lnode *next = node->next;

    if (node->prev != NULL) {
        prev->next = next;
    } else {
        list->head = next;
    }
    if (node->next != NULL) {
        next->prev = prev;
    } else {
        list->tail = prev;
    }

    cspd_free(node->data);
    node->next = NULL;
    node->prev = NULL;
    cspd_free(node);
}
