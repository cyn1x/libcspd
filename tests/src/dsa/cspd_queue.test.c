#include "cspd_dsa.test.h"
#include <cspd_assert.h>
#include <cspd_print.h>
#include <cspd_queue.h>
#include <cspd_types.h>

/******************************************************************************
 * Helper Declarations
 *****************************************************************************/

/* Creates a queue with values from the given array. */
#define tq_from(ARR)                                                           \
    tq_from_impl((ARR), sizeof(ARR) / sizeof((ARR)[0]), sizeof((ARR)[0]))

/* Verifies size, order, and the `front` and `back` pointers of a queue. */
#define tq_expect(TYPE, QUEUE, ARR)                                            \
    do {                                                                       \
        const cspd_queue *_q = (QUEUE);                                        \
        const TYPE       *_e = (ARR);                                          \
        usize             _n = sizeof(ARR) / sizeof((ARR)[0]);                 \
        const cspd_lnode *_c;                                                  \
                                                                               \
        cspd_assert(_q->list.data_size == sizeof(TYPE));                       \
        cspd_assert(_q->front != NULL && _q->back != NULL);                    \
        cspd_assert(_q->front == _q->list.head);                               \
        cspd_assert(_q->back == _q->list.tail);                                \
        cspd_assert(_q->back->next == NULL);                                   \
        cspd_assert((_n == 1) == (_q->front == _q->back));                     \
                                                                               \
        _c = _q->front;                                                        \
        for (usize _i = 0; _i < _n; ++_i) {                                    \
            cspd_assert(_c != NULL);                                           \
            cspd_assert(*(TYPE *)_c->data == _e[_i]);                          \
            _c = _c->next;                                                     \
        }                                                                      \
        cspd_assert(_c == NULL);                                               \
    } while (0)

#define tq_expect_empty(QUEUE)                                                 \
    do {                                                                       \
        const cspd_queue *_q = (QUEUE);                                        \
        cspd_assert(_q->front == NULL);                                        \
        cspd_assert(_q->list.head == NULL);                                    \
    } while (0)

static cspd_queue tq_from_impl(void *values, usize count, usize data_size);

/******************************************************************************
 * Test Declarations
 *****************************************************************************/

static void test_queue_init(void);
static void test_queue_enqueue(void);
static void test_queue_deque(void);
static void test_queue_peek(void);
static void test_queue_clear(void);

/******************************************************************************
 * Test Runner
 *****************************************************************************/

void cspd_queue_test(void)
{
    test_queue_init();
    test_queue_enqueue();
    test_queue_deque();
    test_queue_peek();
    test_queue_clear();
}

/******************************************************************************
 * Test Definitions
 *****************************************************************************/

static void test_queue_init(void)
{
    //! [Initialize]
    cspd_queue queue;
    cspd_queue_init(&queue, sizeof(i32));

    cspd_assert(queue.list.data_size == sizeof(i32));
    cspd_assert(queue.front == NULL && queue.back == NULL);
    //! [Initialize]

    cspd_queue_clear(&queue);
}

static void test_queue_enqueue(void)
{
    {
        cspd_queue queue;
        cspd_queue_init(&queue, sizeof(i32));

        //! [Enqueue]
        i32 a = 1;
        i32 b = 4;
        i32 c = 7;
        i32 d = 9;
        i32 e = 2;

        cspd_queue_enqueue(&queue, &a);
        cspd_queue_enqueue(&queue, &b);
        cspd_queue_enqueue(&queue, &c);
        cspd_queue_enqueue(&queue, &d);
        cspd_queue_enqueue(&queue, &e);

        // Output: { 1 4 7 9 2 }

        cspd_assert(*(i32 *)queue.front->data == 1);
        cspd_assert(*(i32 *)queue.back->data == 2);
        //! [Enqueue]

        i32 expected[] = {1, 4, 7, 9, 2};
        tq_expect(i32, &queue, expected);

        cspd_queue_clear(&queue);
    }

    /* Edge cases */
    {
        // Edge case: first element is both the front and the back
        cspd_queue queue;
        cspd_queue_init(&queue, sizeof(i32));

        i32 a = 1;
        cspd_queue_enqueue(&queue, &a);

        i32 expected[] = {1};
        tq_expect(i32, &queue, expected);

        cspd_queue_clear(&queue);
    }

    {
        // Edge case: the queue owns a copy of the data
        cspd_queue queue;
        cspd_queue_init(&queue, sizeof(i32));

        i32 a = 1;
        cspd_queue_enqueue(&queue, &a);
        a = 5;

        cspd_assert(*(i32 *)queue.front->data == 1);
        cspd_assert(queue.front->data != &a);

        cspd_queue_clear(&queue);
    }
}

static void test_queue_deque(void)
{
    {
        i32        values[] = {1, 4, 7, 9, 2};
        cspd_queue queue    = tq_from(values);

        //! [Deque]
        // Output: { 1 4 7 9 2 }

        cspd_queue_deque(&queue);

        // Output: { 4 7 9 2 }

        cspd_assert(*(i32 *)queue.front->data == 4);
        cspd_assert(*(i32 *)queue.back->data == 2);
        //! [Deque]

        i32 expected[] = {4, 7, 9, 2};
        tq_expect(i32, &queue, expected);

        cspd_queue_clear(&queue);
    }

    /* Edge cases */
    {
        // Edge case: elements leave in first-in, first-out order
        i32        values[] = {1, 4, 7, 9, 2};
        cspd_queue queue    = tq_from(values);

        for (usize i = 0; i < 5; ++i) {
            cspd_assert(*(i32 *)cspd_queue_peek(&queue) == values[i]);
            cspd_queue_deque(&queue);
        }

        tq_expect_empty(&queue);

        cspd_queue_clear(&queue);
    }

    {
        // Edge case: one element remaining is both the front and the back
        i32        values[] = {1, 2};
        cspd_queue queue    = tq_from(values);

        cspd_queue_deque(&queue);

        i32 expected[] = {2};
        tq_expect(i32, &queue, expected);

        cspd_queue_clear(&queue);
    }

    {
        // Edge case: empty queue
        i32        values[] = {1};
        cspd_queue queue    = tq_from(values);

        cspd_queue_deque(&queue);
        cspd_queue_deque(&queue);

        tq_expect_empty(&queue);

        cspd_queue_clear(&queue);
    }

    {
        // Edge case: queue is reusable after being emptied
        i32        values[] = {1};
        cspd_queue queue    = tq_from(values);

        cspd_queue_deque(&queue);

        i32 data = 3;
        cspd_queue_enqueue(&queue, &data);

        i32 expected[] = {3};
        tq_expect(i32, &queue, expected);

        cspd_queue_clear(&queue);
    }
}

static void test_queue_peek(void)
{
    {
        i32        values[] = {1, 4, 7, 9, 2};
        cspd_queue queue    = tq_from(values);

        //! [Peek]
        void *data = cspd_queue_peek(&queue);

        cspd_assert(*(i32 *)data == 1);
        //! [Peek]

        // Peeking does not modify the queue
        cspd_assert(cspd_queue_peek(&queue) == data);
        tq_expect(i32, &queue, values);

        cspd_queue_clear(&queue);
    }

    /* Edge cases */
    {
        // Edge case: single element
        i32        values[] = {1};
        cspd_queue queue    = tq_from(values);

        cspd_assert(*(i32 *)cspd_queue_peek(&queue) == 1);

        cspd_queue_clear(&queue);
    }

    {
        // Edge case: peek follows the front after a deque
        i32        values[] = {1, 4, 7};
        cspd_queue queue    = tq_from(values);

        cspd_queue_deque(&queue);

        cspd_assert(*(i32 *)cspd_queue_peek(&queue) == 4);

        cspd_queue_clear(&queue);
    }
}

static void test_queue_clear(void)
{
    {
        i32        values[] = {1, 4, 7, 9, 2};
        cspd_queue queue    = tq_from(values);

        //! [Clear]
        cspd_queue_clear(&queue);

        cspd_assert(queue.front == NULL);
        cspd_assert(queue.list.head == NULL);
        //! [Clear]
    }

    /* Edge cases */
    {
        // Edge case: empty queue
        cspd_queue queue;
        cspd_queue_init(&queue, sizeof(i32));
        cspd_queue_clear(&queue);

        tq_expect_empty(&queue);
    }

    {
        // Edge case: single element
        i32        values[] = {1};
        cspd_queue queue    = tq_from(values);

        cspd_queue_clear(&queue);

        tq_expect_empty(&queue);
    }

    {
        // Edge case: clearing twice
        i32        values[] = {1, 2, 3};
        cspd_queue queue    = tq_from(values);

        cspd_queue_clear(&queue);
        cspd_queue_clear(&queue);

        tq_expect_empty(&queue);
    }

    {
        // Edge case: queue is reusable after being cleared
        i32        values[] = {1, 2, 3};
        cspd_queue queue    = tq_from(values);

        cspd_queue_clear(&queue);

        i32 data = 4;
        cspd_queue_enqueue(&queue, &data);

        i32 expected[] = {4};
        tq_expect(i32, &queue, expected);

        cspd_queue_clear(&queue);
    }
}

/******************************************************************************
 * Helper Definitions
 *****************************************************************************/

static cspd_queue tq_from_impl(void *values, usize count, usize data_size)
{
    cspd_queue queue;

    cspd_queue_init(&queue, data_size);
    for (usize i = 0; i < count; ++i) {
        cspd_queue_enqueue(&queue, (u8 *)values + i * data_size);
    }

    return queue;
}
