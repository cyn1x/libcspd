#include "linked_list.test.h"
#include "defs.test.h"
#include <assert.h>
#include <linked_list.h>
#include <print.h>

static void    move_test(void);
static void    swap_test(void);
static void    sort_test(void);

static llist_t setup(void)
{
    //! [Initialize]
    llist_t llist;
    llist_init(&llist, sizeof(int32));
    //! [Initialize]

    //! [Comparator function]
    llist._cmp = &int32_cmp; // Set comparator function pointer
    //! [Comparator function]

    //! [Appending nodes]
    int32 a = 7;
    int32 b = 8;
    int32 c = 7;
    int32 d = 3;
    int32 e = 10;
    int32 f = 4;
    int32 g = 5;

    llist_append(&llist, &a);
    llist_append(&llist, &b);
    llist_append(&llist, &c);
    llist_append(&llist, &d);
    llist_append(&llist, &e);
    llist_append(&llist, &f);
    llist_append(&llist, &g);
    //! [Appending nodes]

    return llist;
}

void linked_list_test(void)
{
    llist_t llist_a = setup();
    assert(*(int32 *)llist_a.head->data == 7);
    assert(*(int32 *)llist_a.tail->data == 5);

    //! [Comparator function]
    llist_a._cmp = &int32_cmp; // Set comparator function pointer
    //! [Comparator function]

    llist_t llist_b;

    llist_init(&llist_b, sizeof(int32));
    llist_copy(&llist_b, &llist_a);
    assert(*(int32 *)llist_b.head->data == 7);
    assert(*(int32 *)llist_b.tail->data == 5);

    //! [Comparator function]
    llist_b._cmp = &int32_cmp; // Set comparator function pointer
    //! [Comparator function]

    // print_llist(int32, &llist_a, NULL);
    // Output: { 7 8 7 4 10 3 5 }
    // print_llist(int32, &llist_a, true);
    // Output: { 5 3 10 4 7 8 7 }

    // print_llist(int32, &llist_b, NULL);
    // Output: { 7 8 7 4 10 3 5 }
    // print_llist(int32, &llist_b, true);
    // Output: { 5 3 10 4 7 8 7 }

    int32 h = 1;
    llist_prepend(&llist_a, &h);
    // print_llist(int32, &llist_a, false);
    // Output: { 1 7 8 7 3 10 4 5 }

    int32 i = 9;
    llist_insert(&llist_a, &i, 5);
    // print_llist(int32, &llist_a, false);
    // Output: { 1 7 8 7 3 9 10 4 5 }

    llist_reverse(&llist_a);
    assert(*(int32 *)llist_a.head->data == 5);
    assert(*(int32 *)llist_a.tail->data == 1);

    // print_llist(int32, &llist_a, false);
    // Output: { 5 3 10 9 4 7 8 7 1 }

    {
        int32     k   = 8;
        llnode_t *key = llist_lsearch(&llist_a, &k);
        assert(*(int32 *)key->data == 8);
    }

    size_t idx = llist_index(&llist_a, llist_a.head->next->next);
    assert(idx == 2);

    {
        int32 k = 10;
        llist_delete(&llist_a, &k);
    }

    // print_llist(int32, &llist_a, false);
    // Output: { 5 3 9 4 7 8 7 1 }

    {
        int32 k = 3;
        llist_delete(&llist_a, &k);
        assert(*(int32 *)llist_a.head->data == 5);
    }

    // print_llist(int32, &llist_a, false);
    // Output: { 5 9 4 7 8 7 1 }

    {
        int32 k = 5;
        llist_delete(&llist_a, &k);
        assert(*(int32 *)llist_a.tail->data == 1);
    }

    // print_llist(int32, &llist_a, false);
    // Output: { 4 9 7 8 7 1 }

    int32     start  = 4;
    int32     end    = 1;

    llnode_t *node_a = llist_find(&llist_a, &start);
    llnode_t *node_b = llist_find(&llist_a, &end);

    llist_erase(&llist_a, node_a, node_b);
    assert(*(int32 *)llist_a.head->data == 1);
    assert(*(int32 *)llist_a.tail->data == 1);

    // print_llist(int32, &llist_a, false);
    // Output: { 1 }

    move_test();
    swap_test();
    sort_test();

    llist_clear(&llist_a);
    llist_clear(&llist_b);
    assert(llist_a.head == NULL && llist_a.tail == NULL);
    assert(llist_a.head == NULL && llist_b.tail == NULL);
}

void move_test(void)
{
    llist_t llist = setup();

    llist._cmp    = &int32_cmp; // Set comparator function pointer

    // print_llist(int32, &llist, false);
    // Output: { 7 8 7 3 10 4 5 }

    llist_move(&llist, llist.head->next, llist.tail->prev,
               llist.tail->prev->prev);
    // print_llist(int32, &llist, false);
    // Output: { 7 7 3 10 8 4 5 }
    // print_llist(int32, &llist, true);
    // Output: { 5 4 8 10 3 7 7 }
    assert(*(int32 *)llist.tail->prev->prev->data == 8);

    llist_move(&llist, llist.head->next, llist.tail->prev,
               llist.tail->prev->next);
    // print_llist(int32, &llist, false);
    // Output: { 7 3 10 8 4 7 5 }
    // print_llist(int32, &llist, true);
    // Output: { 5 7 4 8 10 3 7 }
    assert(*(int32 *)llist.tail->prev->data == 7);

    llist_move(&llist, llist.head->next, llist.tail, llist.tail->next);
    // print_llist(int32, &llist, false);
    // Output: { 7 10 8 4 7 5 3 }
    // print_llist(int32, &llist, true);
    // Output: { 3 5 7 4 8 10 7 }
    assert(*(int32 *)llist.tail->prev->next->data == 3);

    llist_move(&llist, llist.head, llist.tail, llist.tail->next);
    // print_llist(int32, &llist, false);
    // Output: { 10 8 4 7 5 3 7 }
    // print_llist(int32, &llist, true);
    // Output: { 7 3 5 7 4 8 10 }
    assert(*(int32 *)llist.tail->prev->next->data == 7);

    llist_move(&llist, llist.head, llist.tail, llist.tail->prev);
    // print_llist(int32, &llist, false);
    // Output: { 8 4 7 5 3 10 7 }
    // print_llist(int32, &llist, true);
    // Output: { 7 10 3 5 7 4 8 }
    assert(*(int32 *)llist.tail->prev->data == 10);

    llist_move(&llist, llist.tail, llist.head, llist.head->prev);
    // print_llist(int32, &llist, false);
    // Output: { 7 8 4 7 5 3 10 }
    // print_llist(int32, &llist, true);
    // Output: { 10 3 5 7 4 8 7 }
    assert(*(int32 *)llist.head->data == 7);

    llist_move(&llist, llist.tail, llist.head, llist.head->next);
    // print_llist(int32, &llist, false);
    // Output: { 7 10 8 4 7 5 3 }
    // print_llist(int32, &llist, true);
    // Output: { 3 5 7 4 8 10 7 }
    assert(*(int32 *)llist.head->next->data == 10);

    llist_move(&llist, llist.head->next->next->next, llist.head,
               llist.head->prev);
    // print_llist(int32, &llist, false);
    // Output: { 4 7 10 8 7 5 3 }
    // print_llist(int32, &llist, true);
    // Output: { 3 5 7 8 10 7 4 }
    assert(*(int32 *)llist.head->data == 4);

    llist_clear(&llist);
    assert(llist.head == NULL && llist.tail == NULL);
}

void swap_test(void)
{
    llist_t llist = setup();

    llist._cmp    = &int32_cmp; // Set comparator function pointer

    // print_llist(int32, &llist, false);
    // Output: { 7 8 7 3 10 4 5 }

    llist_swap(&llist, llist.head->next, llist.tail->prev);
    // print_llist(int32, &llist, false);
    // Output: { 7 4 7 3 10 8 5 }
    assert(*(int32 *)llist.head->next->data == 4);

    llist_swap(&llist, llist.head, llist.tail->prev);
    // print_llist(int32, &llist, false);
    // Output: { 8 4 7 3 10 7 5 }
    assert(*(int32 *)llist.head->data == 8);

    llist_swap(&llist, llist.head, llist.tail);
    // print_llist(int32, &llist, false);
    // Output: { 5 4 7 3 10 7 8 }
    assert(*(int32 *)llist.head->data == 5);
    assert(*(int32 *)llist.tail->data == 8);

    llist_swap(&llist, llist.head->next, llist.head);
    // print_llist(int32, &llist, false);
    // Output: { 4 5 7 3 10 7 8 }
    assert(*(int32 *)llist.head->data == 4);

    llist_swap(&llist, llist.tail, llist.tail->prev);
    // print_llist(int32, &llist, false);
    // Output: { 4 5 7 3 10 8 7 }
    assert(*(int32 *)llist.tail->data == 7);

    llist_swap(&llist, llist.head, llist.head->next);
    // print_llist(int32, &llist, false);
    // Output: { 5 4 7 3 10 8 7 }
    assert(*(int32 *)llist.head->data == 5);

    llist_swap(&llist, llist.tail->prev, llist.tail);
    // print_llist(int32, &llist, false);
    // Output: { 5 4 7 3 10 7 8 }
    assert(*(int32 *)llist.tail->data == 8);

    llist_swap(&llist, llist.head->next->next->next->next->next->next,
               llist.head->next->next->next->next);
    // print_llist(int32, &llist, false);
    // Output: { 5 4 7 3 8 7 10 }
    assert(*(int32 *)llist.tail->data == 10);

    llist_swap(&llist, llist.head->next->next->next->next,
               llist.head->next->next->next->next->next->next);
    // print_llist(int32, &llist, false);
    // Output: { 5 4 7 3 10 7 8 }
    assert(*(int32 *)llist.tail->data == 8);

    llist_clear(&llist);
    assert(llist.head == NULL && llist.tail == NULL);
}

void sort_test(void)
{
    llist_t llist_a = setup();

    llist_a._cmp    = &int32_cmp; // Set comparator function pointer

    llist_t llist_b;
    llist_t llist_c;

    llist_init(&llist_b, sizeof(int32));
    llist_init(&llist_c, sizeof(int32));

    llist_b._cmp = &int32_cmp; // Set comparator function pointer
    llist_c._cmp = &int32_cmp; // Set comparator function pointer

    llist_copy(&llist_b, &llist_a);
    llist_copy(&llist_c, &llist_b);

    llist_reverse(&llist_c);

    {
        int32 a = -1;
        int32 b = 19;
        int32 c = 4;
        int32 d = 33;
        int32 e = 7;
        int32 f = 3;

        //! [Inserting nodes]
        llist_insert(&llist_c, &a, 3);
        llist_insert(&llist_c, &b, 4);
        llist_insert(&llist_c, &c, 5);
        llist_insert(&llist_c, &d, 7);
        llist_insert(&llist_c, &e, 2);
        llist_insert(&llist_c, &f, 9);
        //! [Inserting nodes]
    }

    // print_llist(int32, &llist_a, false);
    // Output: { 7 8 7 4 10 3 5 }

    llist_bsort(&llist_a);
    // print_llist(int32, &llist_a, false);
    // Output: { 3 4 5 7 7 8 10 }
    // print_llist(int32, &llist_a, true);
    // Output: { 10 8 7 7 5 4 3 }
    assert(*(int32 *)llist_a.head->data == 3);
    assert(*(int32 *)llist_a.tail->data == 10);

    // print_llist(int32, &llist_b, false);
    // Output: { 7 8 7 4 10 3 5 }

    llist_qsort(&llist_b, llist_b.head, llist_b.tail);
    // print_llist(int32, &llist_b, false);
    // Output: { 3 4 5 7 7 8 10 }
    // print_llist(int32, &llist_b, true);
    // Output: { 10 8 7 7 5 4 3 }
    assert(*(int32 *)llist_b.head->data == 3);
    assert(*(int32 *)llist_b.tail->data == 10);

    // print_llist(int32, &llist_c, false);
    // Output: { 5 4 7 10 -1 19 4 3 33 3 7 8 7 }

    llist_qsort(&llist_c, llist_c.head, llist_c.tail);
    // print_llist(int32, &llist_c, false);
    // Output: { -1 3 3 4 4 5 7 7 7 8 10 19 33 }
    // print_llist(int32, &llist_c, true);
    // Output: { 33 19 10 8 7 7 7 5 4 4 3 3 -1 }
    assert(*(int32 *)llist_c.head->data == -1);
    assert(*(int32 *)llist_c.tail->data == 33);

    // print_llist(int32, &llist_d, false);
    // Output: { 7 8 7 4 10 3 5 }

    llist_clear(&llist_a);
    llist_clear(&llist_b);
    llist_clear(&llist_c);
    assert(llist_a.head == NULL && llist_a.tail == NULL);
    assert(llist_b.head == NULL && llist_b.tail == NULL);
    assert(llist_c.head == NULL && llist_c.tail == NULL);
}
