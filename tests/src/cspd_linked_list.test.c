#include "cspd_linked_list.test.h"
#include "cspd_defs.test.h"
#include <assert.h>
#include <cspd_linked_list.h>
#include <cspd_print.h>

static void       move_test(void);
static void       swap_test(void);
static void       sort_test(void);

static cspd_llist setup(void)
{
    //! [Initialize]
    cspd_llist llist;
    cspd_llist_init(&llist, sizeof(i32));
    //! [Initialize]

    //! [Appending nodes]
    i32 a = 7;
    i32 b = 8;
    i32 c = 7;
    i32 d = 3;
    i32 e = 10;
    i32 f = 4;
    i32 g = 5;

    cspd_llist_append(&llist, &a);
    cspd_llist_append(&llist, &b);
    cspd_llist_append(&llist, &c);
    cspd_llist_append(&llist, &d);
    cspd_llist_append(&llist, &e);
    cspd_llist_append(&llist, &f);
    cspd_llist_append(&llist, &g);
    //! [Appending nodes]

    return llist;
}

void cspd_linked_list_test(void)
{
    cspd_llist llist_a = setup();
    assert(*(i32 *)llist_a.head->data == 7);
    assert(*(i32 *)llist_a.tail->data == 5);

    cspd_llist llist_b;

    cspd_llist_init(&llist_b, sizeof(i32));
    cspd_llist_copy(&llist_b, &llist_a);
    assert(*(i32 *)llist_b.head->data == 7);
    assert(*(i32 *)llist_b.tail->data == 5);

    // cspd_print_llist(i32, &llist_a, NULL);
    // Output: { 7 8 7 4 10 3 5 }
    // cspd_print_llist(i32, &llist_a, true);
    // Output: { 5 3 10 4 7 8 7 }

    // cspd_print_llist(i32, &llist_b, NULL);
    // Output: { 7 8 7 4 10 3 5 }
    // cspd_print_llist(i32, &llist_b, true);
    // Output: { 5 3 10 4 7 8 7 }

    //! [Prepending nodes]
    i32 h = 1;
    cspd_llist_prepend(&llist_a, &h);
    // cspd_print_llist(i32, &llist_a, false);
    // Output: { 1 7 8 7 3 10 4 5 }
    //! [Prepending nodes]

    //! [Inserting nodes]
    i32 i = 9;
    cspd_llist_insert(&llist_a, &i, 5);
    // cspd_print_llist(i32, &llist_a, false);
    // Output: { 1 7 8 7 3 9 10 4 5 }
    //! [Inserting nodes]

    //! [Reversing nodes]
    cspd_llist_reverse(&llist_a);
    assert(*(i32 *)llist_a.head->data == 5);
    assert(*(i32 *)llist_a.tail->data == 1);

    // cspd_print_llist(i32, &llist_a, false);
    // Output: { 5 3 10 9 4 7 8 7 1 }
    //! [Reversing nodes]

    //! [Linear search]
    {
        i32          k   = 8;
        cspd_llnode *key = cspd_llist_lsearch(&llist_a, &k);
        assert(*(i32 *)key->data == 8);
    }
    //! [Linear search]

    //! [Index of a node]
    size_t idx = cspd_llist_index(&llist_a, llist_a.head->next->next);
    assert(idx == 2);
    //! [Index of a node]

    //! [Deleting nodes]
    // cspd_print_llist(i32, &llist_a, false);
    // Output: { 5 3 10 9 4 7 8 7 1 }

    {
        i32 k = 10;
        cspd_llist_delete(&llist_a, &k);
    }

    // cspd_print_llist(i32, &llist_a, false);
    // Output: { 5 3 9 4 7 8 7 1 }

    {
        i32 k = 3;
        cspd_llist_delete(&llist_a, &k);
        assert(*(i32 *)llist_a.head->data == 5);
    }

    // cspd_print_llist(i32, &llist_a, false);
    // Output: { 5 9 4 7 8 7 1 }

    {
        i32 k = 5;
        cspd_llist_delete(&llist_a, &k);
        assert(*(i32 *)llist_a.tail->data == 1);
    }

    // cspd_print_llist(i32, &llist_a, false);
    // Output: { 4 9 7 8 7 1 }
    //! [Deleting nodes]

    //! [Finding nodes]
    i32          start  = 4;
    i32          end    = 1;

    cspd_llnode *node_a = cspd_llist_find(&llist_a, &start);
    cspd_llnode *node_b = cspd_llist_find(&llist_a, &end);
    assert(*(i32 *)node_a->data == 4);
    assert(*(i32 *)node_b->data == 1);
    //! [Finding nodes]

    //! [Erasing nodes]
    cspd_llist_erase(&llist_a, node_a, node_b);
    assert(*(i32 *)llist_a.head->data == 1);
    assert(*(i32 *)llist_a.tail->data == 1);

    // cspd_print_llist(i32, &llist_a, false);
    // Output: { 1 }
    //! [Erasing nodes]

    move_test();
    swap_test();
    sort_test();

    //! [Clearing lists]
    cspd_llist_clear(&llist_a);
    cspd_llist_clear(&llist_b);
    assert(llist_a.head == NULL && llist_a.tail == NULL);
    assert(llist_a.head == NULL && llist_b.tail == NULL);
    //! [Clearing lists]
}

void move_test(void)
{
    cspd_llist llist = setup();

    //! [Moving nodes]
    // cspd_print_llist(i32, &llist, false);
    // Output: { 7 8 7 3 10 4 5 }

    cspd_llist_move(&llist, llist.head->next, llist.tail->prev,
                    llist.tail->prev->prev);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 7 7 3 10 8 4 5 }
    // cspd_print_llist(i32, &llist, true);
    // Output: { 5 4 8 10 3 7 7 }
    assert(*(i32 *)llist.tail->prev->prev->data == 8);
    //! [Moving nodes]

    cspd_llist_move(&llist, llist.head->next, llist.tail->prev,
                    llist.tail->prev->next);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 7 3 10 8 4 7 5 }
    // cspd_print_llist(i32, &llist, true);
    // Output: { 5 7 4 8 10 3 7 }
    assert(*(i32 *)llist.tail->prev->data == 7);

    cspd_llist_move(&llist, llist.head->next, llist.tail, llist.tail->next);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 7 10 8 4 7 5 3 }
    // cspd_print_llist(i32, &llist, true);
    // Output: { 3 5 7 4 8 10 7 }
    assert(*(i32 *)llist.tail->prev->next->data == 3);

    cspd_llist_move(&llist, llist.head, llist.tail, llist.tail->next);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 10 8 4 7 5 3 7 }
    // cspd_print_llist(i32, &llist, true);
    // Output: { 7 3 5 7 4 8 10 }
    assert(*(i32 *)llist.tail->prev->next->data == 7);

    cspd_llist_move(&llist, llist.head, llist.tail, llist.tail->prev);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 8 4 7 5 3 10 7 }
    // cspd_print_llist(i32, &llist, true);
    // Output: { 7 10 3 5 7 4 8 }
    assert(*(i32 *)llist.tail->prev->data == 10);

    cspd_llist_move(&llist, llist.tail, llist.head, llist.head->prev);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 7 8 4 7 5 3 10 }
    // cspd_print_llist(i32, &llist, true);
    // Output: { 10 3 5 7 4 8 7 }
    assert(*(i32 *)llist.head->data == 7);

    cspd_llist_move(&llist, llist.tail, llist.head, llist.head->next);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 7 10 8 4 7 5 3 }
    // cspd_print_llist(i32, &llist, true);
    // Output: { 3 5 7 4 8 10 7 }
    assert(*(i32 *)llist.head->next->data == 10);

    cspd_llist_move(&llist, llist.head->next->next->next, llist.head,
                    llist.head->prev);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 4 7 10 8 7 5 3 }
    // cspd_print_llist(i32, &llist, true);
    // Output: { 3 5 7 8 10 7 4 }
    assert(*(i32 *)llist.head->data == 4);

    cspd_llist_clear(&llist);
    assert(llist.head == NULL && llist.tail == NULL);
}

void swap_test(void)
{
    cspd_llist llist = setup();

    //! [Swapping nodes]
    // cspd_print_llist(i32, &llist, false);
    // Output: { 7 8 7 3 10 4 5 }

    cspd_llist_swap(&llist, llist.head->next, llist.tail->prev);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 7 4 7 3 10 8 5 }
    assert(*(i32 *)llist.head->next->data == 4);
    //! [Swapping nodes]

    cspd_llist_swap(&llist, llist.head, llist.tail->prev);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 8 4 7 3 10 7 5 }
    assert(*(i32 *)llist.head->data == 8);

    cspd_llist_swap(&llist, llist.head, llist.tail);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 5 4 7 3 10 7 8 }
    assert(*(i32 *)llist.head->data == 5);
    assert(*(i32 *)llist.tail->data == 8);

    cspd_llist_swap(&llist, llist.head->next, llist.head);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 4 5 7 3 10 7 8 }
    assert(*(i32 *)llist.head->data == 4);

    cspd_llist_swap(&llist, llist.tail, llist.tail->prev);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 4 5 7 3 10 8 7 }
    assert(*(i32 *)llist.tail->data == 7);

    cspd_llist_swap(&llist, llist.head, llist.head->next);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 5 4 7 3 10 8 7 }
    assert(*(i32 *)llist.head->data == 5);

    cspd_llist_swap(&llist, llist.tail->prev, llist.tail);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 5 4 7 3 10 7 8 }
    assert(*(i32 *)llist.tail->data == 8);

    cspd_llist_swap(&llist, llist.head->next->next->next->next->next->next,
                    llist.head->next->next->next->next);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 5 4 7 3 8 7 10 }
    assert(*(i32 *)llist.tail->data == 10);

    cspd_llist_swap(&llist, llist.head->next->next->next->next,
                    llist.head->next->next->next->next->next->next);
    // cspd_print_llist(i32, &llist, false);
    // Output: { 5 4 7 3 10 7 8 }
    assert(*(i32 *)llist.tail->data == 8);

    cspd_llist_clear(&llist);
    assert(llist.head == NULL && llist.tail == NULL);
}

void sort_test(void)
{
    cspd_llist llist_a = setup();

    cspd_llist llist_b;
    cspd_llist llist_c;

    cspd_llist_init(&llist_b, sizeof(i32));
    cspd_llist_init(&llist_c, sizeof(i32));

    //! [Copying lists]
    cspd_llist_copy(&llist_b, &llist_a);
    cspd_llist_copy(&llist_c, &llist_b);
    //! [Copying lists]

    cspd_llist_reverse(&llist_c);

    {
        i32 a = -1;
        i32 b = 19;
        i32 c = 4;
        i32 d = 33;
        i32 e = 7;
        i32 f = 3;

        //! [Inserting nodes]
        cspd_llist_insert(&llist_c, &a, 3);
        cspd_llist_insert(&llist_c, &b, 4);
        cspd_llist_insert(&llist_c, &c, 5);
        cspd_llist_insert(&llist_c, &d, 7);
        cspd_llist_insert(&llist_c, &e, 2);
        cspd_llist_insert(&llist_c, &f, 9);
        //! [Inserting nodes]
    }

    // cspd_print_llist(i32, &llist_a, false);
    // Output: { 7 8 7 4 10 3 5 }

    //! [Bubble sort]
    cspd_llist_bsort(&llist_a, i32_cmp);
    // cspd_print_llist(i32, &llist_a, false);
    // Output: { 3 4 5 7 7 8 10 }
    // cspd_print_llist(i32, &llist_a, true);
    // Output: { 10 8 7 7 5 4 3 }
    assert(*(i32 *)llist_a.head->data == 3);
    assert(*(i32 *)llist_a.tail->data == 10);
    //! [Bubble sort]

    // cspd_print_llist(i32, &llist_b, false);
    // Output: { 7 8 7 4 10 3 5 }

    //! [Quicksort]
    cspd_llist_qsort(&llist_b, llist_b.head, llist_b.tail, i32_cmp);
    // cspd_print_llist(i32, &llist_b, false);
    // Output: { 3 4 5 7 7 8 10 }
    // cspd_print_llist(i32, &llist_b, true);
    // Output: { 10 8 7 7 5 4 3 }
    assert(*(i32 *)llist_b.head->data == 3);
    assert(*(i32 *)llist_b.tail->data == 10);
    //! [Quicksort]

    // cspd_print_llist(i32, &llist_c, false);
    // Output: { 5 4 7 10 -1 19 4 3 33 3 7 8 7 }

    cspd_llist_qsort(&llist_c, llist_c.head, llist_c.tail, i32_cmp);
    // cspd_print_llist(i32, &llist_c, false);
    // Output: { -1 3 3 4 4 5 7 7 7 8 10 19 33 }
    // cspd_print_llist(i32, &llist_c, true);
    // Output: { 33 19 10 8 7 7 7 5 4 4 3 3 -1 }
    assert(*(i32 *)llist_c.head->data == -1);
    assert(*(i32 *)llist_c.tail->data == 33);

    cspd_llist_clear(&llist_a);
    cspd_llist_clear(&llist_b);
    cspd_llist_clear(&llist_c);
    assert(llist_a.head == NULL && llist_a.tail == NULL);
    assert(llist_b.head == NULL && llist_b.tail == NULL);
    assert(llist_c.head == NULL && llist_c.tail == NULL);
}
