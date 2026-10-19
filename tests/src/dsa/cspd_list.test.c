#include "cspd_cmp.test.h"
#include "cspd_dsa.test.h"
#include <cspd_assert.h>
#include <cspd_list.h>
#include <cspd_print.h>
#include <cspd_types.h>

/******************************************************************************
 * Helper Declarations
 *****************************************************************************/

/* Creates a linked list of nodes with the values from the given array. */
#define tl_from(ARR)                                                           \
    tl_from_impl((ARR), sizeof(ARR) / sizeof((ARR)[0]), sizeof((ARR)[0]))

/* Verifies size, order, and the integrity of both `next` and `prev` links. */
#define tl_expect(TYPE, LIST, ARR)                                             \
    do {                                                                       \
        const cspd_list  *_l = (LIST);                                         \
        const TYPE       *_e = (ARR);                                          \
        usize             _n = sizeof(ARR) / sizeof((ARR)[0]);                 \
        const cspd_lnode *_c;                                                  \
                                                                               \
        cspd_assert(_l->data_size == sizeof(TYPE));                            \
        cspd_assert(_l->head != NULL && _l->tail != NULL);                     \
        cspd_assert(_l->head->prev == NULL && _l->tail->next == NULL);         \
        cspd_assert((_n == 1) == (_l->head == _l->tail));                      \
                                                                               \
        _c = _l->head;                                                         \
        for (usize _i = 0; _i < _n; ++_i) {                                    \
            cspd_assert(_c != NULL);                                           \
            cspd_assert(*(TYPE *)_c->data == _e[_i]);                          \
            _c = _c->next;                                                     \
        }                                                                      \
        cspd_assert(_c == NULL);                                               \
                                                                               \
        _c = _l->tail;                                                         \
        for (usize _i = _n; _i > 0; --_i) {                                    \
            cspd_assert(_c != NULL);                                           \
            cspd_assert(*(TYPE *)_c->data == _e[_i - 1]);                      \
            _c = _c->prev;                                                     \
        }                                                                      \
        cspd_assert(_c == NULL);                                               \
    } while (0)

#define tl_expect_empty(LIST)                                                  \
    do {                                                                       \
        const cspd_list *_l = (LIST);                                          \
        cspd_assert(_l->head == NULL);                                         \
        cspd_assert(_l->tail == NULL);                                         \
    } while (0)

static cspd_list tl_from_impl(void *values, usize count, usize data_size);

/******************************************************************************
 * Test Declarations
 *****************************************************************************/

static void test_list_init(void);
static void test_list_append(void);
static void test_list_prepend(void);
static void test_list_insert(void);
static void test_list_move(void);
static void test_list_swap(void);
static void test_list_delete(void);
static void test_list_erase(void);
static void test_list_clear(void);
static void test_list_copy(void);
static void test_list_reverse(void);
static void test_list_index(void);
static void test_list_find(void);
static void test_list_lsearch(void);
static void test_list_bsort(void);
static void test_list_qsort(void);

/******************************************************************************
 * Test Runner
 *****************************************************************************/

void cspd_list_test(void)
{
    test_list_init();
    test_list_append();
    test_list_prepend();
    test_list_insert();
    test_list_move();
    test_list_swap();
    test_list_delete();
    test_list_erase();
    test_list_clear();
    test_list_copy();
    test_list_reverse();
    test_list_index();
    test_list_find();
    test_list_lsearch();
    test_list_bsort();
    test_list_qsort();
}

/******************************************************************************
 * Test Definitions
 *****************************************************************************/

static void test_list_init(void)
{
    //! [Initialize linked list]
    cspd_list llist;
    cspd_list_init(&llist, sizeof(i32));

    // cspd_print_list(i32, &llist, false);
    // Output: { }

    cspd_assert(llist.data_size == sizeof(i32));
    cspd_assert(llist.head == NULL && llist.tail == NULL);
    //! [Initialize linked list]

    cspd_list_clear(&llist);
}

static void test_list_append(void)
{
    {
        //! [Appending nodes]
        cspd_list llist;
        cspd_list_init(&llist, sizeof(i32));

        i32 a = 7;
        i32 b = 8;
        i32 c = 7;
        i32 d = 3;
        i32 e = 10;
        i32 f = 4;
        i32 g = 5;

        cspd_list_append(&llist, &a);
        cspd_list_append(&llist, &b);
        cspd_list_append(&llist, &c);
        cspd_list_append(&llist, &d);
        cspd_list_append(&llist, &e);
        cspd_list_append(&llist, &f);
        cspd_list_append(&llist, &g);

        // cspd_print_list(i32, &llist, false);
        // Output: { 7 8 7 3 10 4 5 }
        // cspd_print_list(i32, &llist, true);
        // Output: { 5 4 10 3 7 8 7 }

        cspd_assert(*(i32 *)llist.head->data == 7);
        cspd_assert(*(i32 *)llist.tail->data == 5);
        //! [Appending nodes]

        i32 expected[] = {7, 8, 7, 3, 10, 4, 5};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    /* Edge cases */
    {
        // Edge case: empty list
        cspd_list llist;
        cspd_list_init(&llist, sizeof(i32));

        i32 a = 1;
        cspd_list_append(&llist, &a);

        i32 expected[] = {1};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }
}

static void test_list_prepend(void)
{
    {
        i32       values[] = {7, 8, 7, 3, 10, 4, 5};
        cspd_list llist    = tl_from(values);

        //! [Prepending nodes]
        // cspd_print_list(i32, &llist, false);
        // Output: { 7 8 7 3 10 4 5 }

        i32 data = 1;
        cspd_list_prepend(&llist, &data);

        // cspd_print_list(i32, &llist, false);
        // Output: { 1 7 8 7 3 10 4 5 }

        cspd_assert(*(i32 *)llist.head->data == 1);
        cspd_assert(*(i32 *)llist.head->next->data == 7);
        //! [Prepending nodes]

        i32 expected[] = {1, 7, 8, 7, 3, 10, 4, 5};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    /* Edge cases */
    {
        // Edge case: empty list
        cspd_list llist;
        cspd_list_init(&llist, sizeof(i32));

        i32 data = 1;
        cspd_list_prepend(&llist, &data);

        i32 expected[] = {1};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: single element
        i32       values[] = {2};
        cspd_list llist    = tl_from(values);

        i32 data           = 1;
        cspd_list_prepend(&llist, &data);

        i32 expected[] = {1, 2};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }
}

static void test_list_insert(void)
{
    {
        i32       values[] = {1, 7, 8, 7, 3, 10, 4, 5};
        cspd_list llist    = tl_from(values);

        //! [Inserting nodes]
        // cspd_print_list(i32, &llist, false);
        // Output: { 1 7 8 7 3 10 4 5 }

        i32 data = 9;
        cspd_list_insert(&llist, &data, 5);

        // cspd_print_list(i32, &llist, false);
        // Output: { 1 7 8 7 3 9 10 4 5 }

        cspd_lnode *node = cspd_list_find(&llist, &data);
        cspd_assert(cspd_list_index(&llist, node) == 5);
        //! [Inserting nodes]

        i32 expected[] = {1, 7, 8, 7, 3, 9, 10, 4, 5};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    /* Edge cases */
    {
        // Edge case: front
        i32       values[] = {1, 2, 3};
        cspd_list llist    = tl_from(values);

        i32 data           = 0;
        cspd_list_insert(&llist, &data, 0);

        i32 expected[] = {0, 1, 2, 3};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: immediately before the tail
        i32       values[] = {0, 1, 2};
        cspd_list llist    = tl_from(values);

        i32 data           = 9;
        cspd_list_insert(&llist, &data, 2);

        i32 expected[] = {0, 1, 9, 2};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }
}

static void test_list_move(void)
{
    {
        i32       values[] = {7, 8, 7, 3, 10, 4, 5};
        cspd_list llist    = tl_from(values);

        //! [Moving nodes]
        // cspd_print_list(i32, &llist, false);
        // Output: { 7 8 7 3 10 4 5 }

        cspd_list_move(&llist, llist.head->next, llist.tail->prev,
                       llist.tail->prev->prev);

        // cspd_print_list(i32, &llist, false);
        // Output: { 7 7 3 10 8 4 5 }
        // cspd_print_list(i32, &llist, true);
        // Output: { 5 4 8 10 3 7 7 }

        cspd_assert(*(i32 *)llist.tail->prev->prev->data == 8);
        //! [Moving nodes]

        {
            i32 expected[] = {7, 7, 3, 10, 8, 4, 5};
            tl_expect(i32, &llist, expected);
        }

        // Interior node to the `next` side of an interior destination
        cspd_list_move(&llist, llist.head->next, llist.tail->prev,
                       llist.tail->prev->next);
        {
            i32 expected[] = {7, 3, 10, 8, 4, 7, 5};
            tl_expect(i32, &llist, expected);
        }

        // Interior node to after the tail
        cspd_list_move(&llist, llist.head->next, llist.tail, llist.tail->next);
        {
            i32 expected[] = {7, 10, 8, 4, 7, 5, 3};
            tl_expect(i32, &llist, expected);
        }

        // Head to after the tail
        cspd_list_move(&llist, llist.head, llist.tail, llist.tail->next);
        {
            i32 expected[] = {10, 8, 4, 7, 5, 3, 7};
            tl_expect(i32, &llist, expected);
        }

        // Head to before the tail
        cspd_list_move(&llist, llist.head, llist.tail, llist.tail->prev);
        {
            i32 expected[] = {8, 4, 7, 5, 3, 10, 7};
            tl_expect(i32, &llist, expected);
        }

        // Tail to before the head
        cspd_list_move(&llist, llist.tail, llist.head, llist.head->prev);
        {
            i32 expected[] = {7, 8, 4, 7, 5, 3, 10};
            tl_expect(i32, &llist, expected);
        }

        // Tail to after the head
        cspd_list_move(&llist, llist.tail, llist.head, llist.head->next);
        {
            i32 expected[] = {7, 10, 8, 4, 7, 5, 3};
            tl_expect(i32, &llist, expected);
        }

        // Interior node to before the head
        cspd_list_move(&llist, llist.head->next->next->next, llist.head,
                       llist.head->prev);
        {
            i32 expected[] = {4, 7, 10, 8, 7, 5, 3};
            tl_expect(i32, &llist, expected);
        }

        cspd_list_clear(&llist);
    }

    /* Edge cases */
    {
        // Edge case: node and destination are the same
        i32       values[] = {1, 2, 3, 4};
        cspd_list llist    = tl_from(values);

        cspd_list_move(&llist, llist.head, llist.head, llist.head->next);
        tl_expect(i32, &llist, values);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: destination pointer does not belong to the destination
        i32       values[] = {1, 2, 3, 4};
        cspd_list llist    = tl_from(values);

        cspd_list_move(&llist, llist.head, llist.tail, llist.head);
        tl_expect(i32, &llist, values);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: node is adjacent to the destination
        i32       values[] = {1, 2, 3, 4};
        cspd_list llist    = tl_from(values);

        cspd_list_move(&llist, llist.head, llist.head->next,
                       llist.head->next->next);

        i32 expected[] = {2, 1, 3, 4};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }
}

static void test_list_swap(void)
{
    {
        i32       values[] = {7, 8, 7, 3, 10, 4, 5};
        cspd_list llist    = tl_from(values);

        //! [Swapping nodes]
        // cspd_print_list(i32, &llist, false);
        // Output: { 7 8 7 3 10 4 5 }

        cspd_list_swap(&llist, llist.head->next, llist.tail->prev);

        // cspd_print_list(i32, &llist, false);
        // Output: { 7 4 7 3 10 8 5 }

        cspd_assert(*(i32 *)llist.head->next->data == 4);
        cspd_assert(*(i32 *)llist.tail->prev->data == 8);
        //! [Swapping nodes]

        {
            i32 expected[] = {7, 4, 7, 3, 10, 8, 5};
            tl_expect(i32, &llist, expected);
        }

        // Head with an interior node
        cspd_list_swap(&llist, llist.head, llist.tail->prev);
        {
            i32 expected[] = {8, 4, 7, 3, 10, 7, 5};
            tl_expect(i32, &llist, expected);
        }

        // Head with tail
        cspd_list_swap(&llist, llist.head, llist.tail);
        {
            i32 expected[] = {5, 4, 7, 3, 10, 7, 8};
            tl_expect(i32, &llist, expected);
        }

        // Adjacent nodes at the head, arguments in reverse order
        cspd_list_swap(&llist, llist.head->next, llist.head);
        {
            i32 expected[] = {4, 5, 7, 3, 10, 7, 8};
            tl_expect(i32, &llist, expected);
        }

        // Adjacent nodes at the tail, arguments in reverse order
        cspd_list_swap(&llist, llist.tail, llist.tail->prev);
        {
            i32 expected[] = {4, 5, 7, 3, 10, 8, 7};
            tl_expect(i32, &llist, expected);
        }

        // Adjacent nodes at the head
        cspd_list_swap(&llist, llist.head, llist.head->next);
        {
            i32 expected[] = {5, 4, 7, 3, 10, 8, 7};
            tl_expect(i32, &llist, expected);
        }

        // Adjacent nodes at the tail
        cspd_list_swap(&llist, llist.tail->prev, llist.tail);
        {
            i32 expected[] = {5, 4, 7, 3, 10, 7, 8};
            tl_expect(i32, &llist, expected);
        }

        // Non-adjacent nodes with a single node between them
        cspd_list_swap(&llist, llist.head->next->next->next->next->next->next,
                       llist.head->next->next->next->next);
        {
            i32 expected[] = {5, 4, 7, 3, 8, 7, 10};
            tl_expect(i32, &llist, expected);
        }

        // Same swap with the arguments in reverse order
        cspd_list_swap(&llist, llist.head->next->next->next->next,
                       llist.head->next->next->next->next->next->next);
        {
            i32 expected[] = {5, 4, 7, 3, 10, 7, 8};
            tl_expect(i32, &llist, expected);
        }

        cspd_list_clear(&llist);
    }

    /* Edge cases */
    {
        // Edge case: two element list
        i32       values[] = {1, 2};
        cspd_list llist    = tl_from(values);

        cspd_list_swap(&llist, llist.head, llist.tail);

        i32 expected[] = {2, 1};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }
}

static void test_list_delete(void)
{
    {
        i32       values[] = {5, 4, 10, 9, 3, 7, 8, 7, 1};
        cspd_list llist    = tl_from(values);

        //! [Deleting nodes]
        // cspd_print_list(i32, &llist, false);
        // Output: { 5 4 10 9 3 7 8 7 1 }

        // Delete a node from the middle
        i32 key = 10;
        cspd_list_delete(&llist, &key);

        // cspd_print_list(i32, &llist, false);
        // Output: { 5 4 9 3 7 8 7 1 }

        // Delete the head
        key = 5;
        cspd_list_delete(&llist, &key);
        cspd_assert(*(i32 *)llist.head->data == 4);

        // cspd_print_list(i32, &llist, false);
        // Output: { 4 9 3 7 8 7 1 }

        // Delete the tail
        key = 1;
        cspd_list_delete(&llist, &key);
        cspd_assert(*(i32 *)llist.tail->data == 7);

        // cspd_print_list(i32, &llist, false);
        // Output: { 4 9 3 7 8 7 }
        //! [Deleting nodes]

        i32 expected[] = {4, 9, 3, 7, 8, 7};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    /* Edge cases */
    {
        // Edge case: key not found
        i32       values[] = {1, 2, 3};
        cspd_list llist    = tl_from(values);

        i32 key            = 9;
        cspd_list_delete(&llist, &key);

        tl_expect(i32, &llist, values);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: duplicate keys, only the first match is deleted
        i32       values[] = {7, 8, 7};
        cspd_list llist    = tl_from(values);

        i32 key            = 7;
        cspd_list_delete(&llist, &key);

        i32 expected[] = {8, 7};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: single element
        i32       values[] = {1};
        cspd_list llist    = tl_from(values);

        i32 key            = 1;
        cspd_list_delete(&llist, &key);

        tl_expect_empty(&llist);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: empty list
        cspd_list llist;
        cspd_list_init(&llist, sizeof(i32));

        i32 key = 1;
        cspd_list_delete(&llist, &key);

        tl_expect_empty(&llist);

        cspd_list_clear(&llist);
    }
}

static void test_list_erase(void)
{
    {
        i32       values[] = {4, 9, 7, 8, 7, 1};
        cspd_list llist    = tl_from(values);

        //! [Erasing nodes]
        // cspd_print_list(i32, &llist, false);
        // Output: { 4 9 7 8 7 1 }

        i32 start          = 4;
        i32 end            = 1;

        cspd_lnode *node_a = cspd_list_find(&llist, &start);
        cspd_lnode *node_b = cspd_list_find(&llist, &end);

        // The erasure includes `node_a` and excludes `node_b`, i.e. [a, b)
        cspd_list_erase(&llist, node_a, node_b);

        // cspd_print_list(i32, &llist, false);
        // Output: { 1 }

        cspd_assert(llist.head == llist.tail);
        cspd_assert(*(i32 *)llist.head->data == 1);
        //! [Erasing nodes]

        i32 expected[] = {1};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    /* Edge cases */
    {
        // Edge case: range starting at the head
        i32       values[] = {1, 2, 3, 4};
        cspd_list llist    = tl_from(values);

        cspd_list_erase(&llist, llist.head, llist.head->next->next);

        i32 expected[] = {3, 4};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: range ending at NULL erases through the tail
        i32       values[] = {1, 2, 3, 4};
        cspd_list llist    = tl_from(values);

        cspd_list_erase(&llist, llist.head->next, NULL);

        i32 expected[] = {1};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: whole list
        i32       values[] = {1, 2, 3, 4};
        cspd_list llist    = tl_from(values);

        cspd_list_erase(&llist, llist.head, NULL);

        tl_expect_empty(&llist);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: empty range
        i32       values[] = {1, 2, 3, 4};
        cspd_list llist    = tl_from(values);

        cspd_list_erase(&llist, llist.head->next, llist.head->next);

        tl_expect(i32, &llist, values);

        cspd_list_clear(&llist);
    }
}

static void test_list_clear(void)
{
    {
        i32       values[] = {7, 8, 7, 3, 10, 4, 5};
        cspd_list llist    = tl_from(values);

        //! [Clearing lists]
        cspd_list_clear(&llist);

        cspd_assert(llist.head == NULL && llist.tail == NULL);
        //! [Clearing lists]
    }

    /* Edge cases */
    {
        // Edge case: empty list
        cspd_list llist;
        cspd_list_init(&llist, sizeof(i32));
        cspd_list_clear(&llist);

        tl_expect_empty(&llist);
    }

    {
        // Edge case: list is reusable after being cleared
        i32       values[] = {1, 2, 3};
        cspd_list llist    = tl_from(values);

        cspd_list_clear(&llist);

        i32 data = 4;
        cspd_list_append(&llist, &data);

        i32 expected[] = {4};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }
}

static void test_list_copy(void)
{
    {
        i32       values[] = {7, 8, 7, 3, 10, 4, 5};
        cspd_list llist_a  = tl_from(values);

        //! [Copying lists]
        cspd_list llist_b;
        cspd_list_init(&llist_b, sizeof(i32));
        cspd_list_copy(&llist_b, &llist_a);

        // cspd_print_list(i32, &llist_b, false);
        // Output: { 7 8 7 3 10 4 5 }

        cspd_assert(*(i32 *)llist_b.head->data == 7);
        cspd_assert(*(i32 *)llist_b.tail->data == 5);
        //! [Copying lists]

        tl_expect(i32, &llist_a, values);
        tl_expect(i32, &llist_b, values);

        // The copy owns its memory
        cspd_assert(llist_a.head != llist_b.head);
        cspd_assert(llist_a.head->data != llist_b.head->data);

        cspd_list_clear(&llist_a);
        cspd_list_clear(&llist_b);
    }

    /* Edge cases */
    {
        // Edge case: non-empty destination is replaced
        i32       src_values[] = {7, 8, 7};
        i32       dst_values[] = {1, 2};
        cspd_list src          = tl_from(src_values);
        cspd_list dst          = tl_from(dst_values);

        cspd_list_copy(&dst, &src);

        tl_expect(i32, &dst, src_values);

        cspd_list_clear(&src);
        cspd_list_clear(&dst);
    }

    {
        // Edge case: empty source clears the destination
        i32       dst_values[] = {1, 2};
        cspd_list src;
        cspd_list dst = tl_from(dst_values);

        cspd_list_init(&src, sizeof(i32));
        cspd_list_copy(&dst, &src);

        tl_expect_empty(&dst);

        cspd_list_clear(&src);
        cspd_list_clear(&dst);
    }
}

static void test_list_reverse(void)
{
    {
        i32       values[] = {1, 7, 8, 7, 3, 9, 10, 4, 5};
        cspd_list llist    = tl_from(values);

        //! [Reversing nodes]
        // cspd_print_list(i32, &llist, false);
        // Output: { 1 7 8 7 3 9 10 4 5 }

        cspd_list_reverse(&llist);

        // cspd_print_list(i32, &llist, false);
        // Output: { 5 4 10 9 3 7 8 7 1 }

        cspd_assert(*(i32 *)llist.head->data == 5);
        cspd_assert(*(i32 *)llist.tail->data == 1);
        //! [Reversing nodes]

        i32 expected[] = {5, 4, 10, 9, 3, 7, 8, 7, 1};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    /* Edge cases */
    {
        // Edge case: empty list
        cspd_list llist;
        cspd_list_init(&llist, sizeof(i32));

        cspd_list_reverse(&llist);

        tl_expect_empty(&llist);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: single element
        i32       values[] = {1};
        cspd_list llist    = tl_from(values);

        cspd_list_reverse(&llist);

        tl_expect(i32, &llist, values);

        cspd_list_clear(&llist);
    }
}

static void test_list_index(void)
{
    i32       values[] = {5, 4, 10, 9, 3, 7, 8, 7, 1};
    cspd_list llist    = tl_from(values);

    //! [Index of a node]
    // cspd_print_list(i32, &llist, false);
    // Output: { 5 4 10 9 3 7 8 7 1 }

    usize idx = cspd_list_index(&llist, llist.head->next->next);

    cspd_assert(idx == 2);
    //! [Index of a node]

    cspd_assert(cspd_list_index(&llist, llist.head) == 0);
    cspd_assert(cspd_list_index(&llist, llist.tail) == 8);

    cspd_list_clear(&llist);
}

static void test_list_find(void)
{
    i32       values[] = {4, 9, 7, 8, 7, 1};
    cspd_list llist    = tl_from(values);

    //! [Finding nodes]
    // cspd_print_list(i32, &llist, false);
    // Output: { 4 9 7 8 7 1 }

    i32 start          = 4;
    i32 end            = 1;

    cspd_lnode *node_a = cspd_list_find(&llist, &start);
    cspd_lnode *node_b = cspd_list_find(&llist, &end);

    cspd_assert(node_a == llist.head && *(i32 *)node_a->data == 4);
    cspd_assert(node_b == llist.tail && *(i32 *)node_b->data == 1);
    //! [Finding nodes]

    /* Edge cases */
    {
        // Edge case: key not found
        i32 key = 99;
        cspd_assert(cspd_list_find(&llist, &key) == NULL);
    }

    cspd_list_clear(&llist);
}

static void test_list_lsearch(void)
{
    i32       values[] = {7, 8, 7, 3, 10, 4, 5};
    cspd_list llist    = tl_from(values);

    //! [Linear search]
    // cspd_print_list(i32, &llist, false);
    // Output: { 7 8 7 3 10 4 5 }

    i32         key  = 8;
    cspd_lnode *node = cspd_list_lsearch(&llist, &key);

    cspd_assert(node != NULL && *(i32 *)node->data == 8);
    //! [Linear search]

    /* Edge cases */
    {
        // Edge case: key not found
        i32 missing = 99;
        cspd_assert(cspd_list_lsearch(&llist, &missing) == NULL);
    }

    {
        // Edge case: duplicate keys return the first match
        i32 dup = 7;
        cspd_assert(cspd_list_lsearch(&llist, &dup) == llist.head);
    }

    {
        // Edge case: key at the tail
        i32 last = 5;
        cspd_assert(cspd_list_lsearch(&llist, &last) == llist.tail);
    }

    cspd_list_clear(&llist);

    {
        // Edge case: empty list
        cspd_list empty;
        cspd_list_init(&empty, sizeof(i32));

        i32 k = 1;
        cspd_assert(cspd_list_lsearch(&empty, &k) == NULL);

        cspd_list_clear(&empty);
    }
}

static void test_list_bsort(void)
{
    {
        i32       values[] = {7, 8, 7, 3, 10, 4, 5};
        cspd_list llist    = tl_from(values);

        //! [Bubble sort]
        // cspd_print_list(i32, &llist, false);
        // Output: { 7 8 7 3 10 4 5 }

        cspd_list_bsort(&llist, i32_cmp);

        // cspd_print_list(i32, &llist, false);
        // Output: { 3 4 5 7 7 8 10 }
        // cspd_print_list(i32, &llist, true);
        // Output: { 10 8 7 7 5 4 3 }

        cspd_assert(*(i32 *)llist.head->data == 3);
        cspd_assert(*(i32 *)llist.tail->data == 10);
        //! [Bubble sort]

        i32 expected[] = {3, 4, 5, 7, 7, 8, 10};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    /* Edge cases */
    {
        // Edge case: negative and duplicate values
        i32       values[] = {5, 4, 7, 10, -1, 19, 4, 3, 33, 3, 7, 8, 7};
        cspd_list llist    = tl_from(values);

        cspd_list_bsort(&llist, i32_cmp);

        i32 expected[] = {-1, 3, 3, 4, 4, 5, 7, 7, 7, 8, 10, 19, 33};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: already sorted
        i32       values[] = {1, 2, 3, 4, 5};
        cspd_list llist    = tl_from(values);

        cspd_list_bsort(&llist, i32_cmp);

        tl_expect(i32, &llist, values);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: empty list
        cspd_list llist;
        cspd_list_init(&llist, sizeof(i32));

        cspd_list_bsort(&llist, i32_cmp);

        tl_expect_empty(&llist);

        cspd_list_clear(&llist);
    }
}

static void test_list_qsort(void)
{
    {
        i32       values[] = {7, 8, 7, 3, 10, 4, 5};
        cspd_list llist    = tl_from(values);

        //! [Quicksort]
        // cspd_print_list(i32, &llist, false);
        // Output: { 7 8 7 3 10 4 5 }

        cspd_list_qsort(&llist, llist.head, llist.tail, i32_cmp);

        // cspd_print_list(i32, &llist, false);
        // Output: { 3 4 5 7 7 8 10 }
        // cspd_print_list(i32, &llist, true);
        // Output: { 10 8 7 7 5 4 3 }

        cspd_assert(*(i32 *)llist.head->data == 3);
        cspd_assert(*(i32 *)llist.tail->data == 10);
        //! [Quicksort]

        i32 expected[] = {3, 4, 5, 7, 7, 8, 10};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    /* Edge cases */
    {
        // Edge case: negative and duplicate values
        i32       values[] = {5, 4, 7, 10, -1, 19, 4, 3, 33, 3, 7, 8, 7};
        cspd_list llist    = tl_from(values);

        cspd_list_qsort(&llist, llist.head, llist.tail, i32_cmp);

        i32 expected[] = {-1, 3, 3, 4, 4, 5, 7, 7, 7, 8, 10, 19, 33};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: already sorted
        i32       values[] = {1, 2, 3, 4, 5};
        cspd_list llist    = tl_from(values);

        cspd_list_qsort(&llist, llist.head, llist.tail, i32_cmp);

        tl_expect(i32, &llist, values);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: reverse sorted
        i32       values[] = {5, 4, 3, 2, 1};
        cspd_list llist    = tl_from(values);

        cspd_list_qsort(&llist, llist.head, llist.tail, i32_cmp);

        i32 expected[] = {1, 2, 3, 4, 5};
        tl_expect(i32, &llist, expected);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: single element
        i32       values[] = {1};
        cspd_list llist    = tl_from(values);

        cspd_list_qsort(&llist, llist.head, llist.tail, i32_cmp);

        tl_expect(i32, &llist, values);

        cspd_list_clear(&llist);
    }

    {
        // Edge case: empty list
        cspd_list llist;
        cspd_list_init(&llist, sizeof(i32));

        cspd_list_qsort(&llist, llist.head, llist.tail, i32_cmp);

        tl_expect_empty(&llist);

        cspd_list_clear(&llist);
    }
}

/******************************************************************************
 * Helper Definitions
 *****************************************************************************/

static cspd_list tl_from_impl(void *values, usize count, usize data_size)
{
    cspd_list list;

    cspd_list_init(&list, data_size);
    for (usize i = 0; i < count; ++i) {
        cspd_list_append(&list, (u8 *)values + i * data_size);
    }

    return list;
}
