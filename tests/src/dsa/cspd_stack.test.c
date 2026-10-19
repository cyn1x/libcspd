#include "cspd_dsa.test.h"
#include <cspd_assert.h>
#include <cspd_print.h>
#include <cspd_stack.h>
#include <cspd_types.h>

/******************************************************************************
 * Helper Declarations
 *****************************************************************************/

/* Pushes each element in array order, so the last element ends up on top. */
#define ts_from(ARR)                                                           \
    ts_from_impl((ARR), sizeof(ARR) / sizeof((ARR)[0]), sizeof((ARR)[0]))

/* Verifies size, order, and the `top` and `bottom` pointers of a stack. The
 * expected array is ordered from the top of the stack to the bottom. */
#define ts_expect(TYPE, STACK, ARR)                                            \
    do {                                                                       \
        const cspd_stack *_s = (STACK);                                        \
        const TYPE       *_e = (ARR);                                          \
        usize             _n = sizeof(ARR) / sizeof((ARR)[0]);                 \
        const cspd_lnode *_c;                                                  \
                                                                               \
        cspd_assert(_s->list.data_size == sizeof(TYPE));                       \
        cspd_assert(_s->top != NULL && _s->bottom != NULL);                    \
        cspd_assert(_s->top == _s->list.head);                                 \
        cspd_assert(_s->bottom == _s->list.tail);                              \
        cspd_assert(_s->bottom->next == NULL);                                 \
        cspd_assert((_n == 1) == (_s->top == _s->bottom));                     \
                                                                               \
        _c = _s->top;                                                          \
        for (usize _i = 0; _i < _n; ++_i) {                                    \
            cspd_assert(_c != NULL);                                           \
            cspd_assert(*(TYPE *)_c->data == _e[_i]);                          \
            _c = _c->next;                                                     \
        }                                                                      \
        cspd_assert(_c == NULL);                                               \
    } while (0)

#define ts_expect_empty(STACK)                                                 \
    do {                                                                       \
        const cspd_stack *_s = (STACK);                                        \
        cspd_assert(_s->top == NULL);                                          \
        cspd_assert(_s->list.head == NULL);                                    \
    } while (0)

static cspd_stack ts_from_impl(void *values, usize count, usize data_size);

/******************************************************************************
 * Test Declarations
 *****************************************************************************/

static void test_stack_init(void);
static void test_stack_push(void);
static void test_stack_pop(void);
static void test_stack_peek(void);
static void test_stack_clear(void);

/******************************************************************************
 * Test Runner
 *****************************************************************************/

void cspd_stack_test(void)
{
    test_stack_init();
    test_stack_push();
    test_stack_pop();
    test_stack_peek();
    test_stack_clear();
}

/******************************************************************************
 * Test Definitions
 *****************************************************************************/

static void test_stack_init(void)
{
    //! [Initialize]
    cspd_stack stack;
    cspd_stack_init(&stack, sizeof(i32));

    cspd_assert(stack.list.data_size == sizeof(i32));
    cspd_assert(stack.top == NULL && stack.bottom == NULL);
    //! [Initialize]

    cspd_stack_clear(&stack);
}

static void test_stack_push(void)
{
    {
        cspd_stack stack;
        cspd_stack_init(&stack, sizeof(i32));

        //! [Push]
        i32 a = 1;
        i32 b = 4;
        i32 c = 7;
        i32 d = 9;
        i32 e = 2;

        cspd_stack_push(&stack, &a);
        cspd_stack_push(&stack, &b);
        cspd_stack_push(&stack, &c);
        cspd_stack_push(&stack, &d);
        cspd_stack_push(&stack, &e);

        // Output (top to bottom): { 2 9 7 4 1 }

        cspd_assert(*(i32 *)stack.top->data == 2);
        cspd_assert(*(i32 *)stack.bottom->data == 1);
        //! [Push]

        i32 expected[] = {2, 9, 7, 4, 1};
        ts_expect(i32, &stack, expected);

        cspd_stack_clear(&stack);
    }

    /* Edge cases */
    {
        // Edge case: first element is both the top and the bottom
        cspd_stack stack;
        cspd_stack_init(&stack, sizeof(i32));

        i32 a = 1;
        cspd_stack_push(&stack, &a);

        i32 expected[] = {1};
        ts_expect(i32, &stack, expected);

        cspd_stack_clear(&stack);
    }

    {
        // Edge case: second element becomes the top, bottom is unchanged
        cspd_stack stack;
        cspd_stack_init(&stack, sizeof(i32));

        i32 a = 1;
        i32 b = 2;
        cspd_stack_push(&stack, &a);
        cspd_stack_push(&stack, &b);

        i32 expected[] = {2, 1};
        ts_expect(i32, &stack, expected);

        cspd_stack_clear(&stack);
    }

    {
        // Edge case: the stack owns a copy of the data
        cspd_stack stack;
        cspd_stack_init(&stack, sizeof(i32));

        i32 a = 1;
        cspd_stack_push(&stack, &a);
        a = 5;

        cspd_assert(*(i32 *)stack.top->data == 1);
        cspd_assert(stack.top->data != &a);

        cspd_stack_clear(&stack);
    }
}

static void test_stack_pop(void)
{
    {
        i32        values[] = {1, 4, 7, 9, 2};
        cspd_stack stack    = ts_from(values);

        //! [Pop]
        // Output (top to bottom): { 2 9 7 4 1 }

        cspd_stack_pop(&stack);

        // Output (top to bottom): { 9 7 4 1 }

        cspd_assert(*(i32 *)stack.top->data == 9);
        cspd_assert(*(i32 *)stack.bottom->data == 1);
        //! [Pop]

        i32 expected[] = {9, 7, 4, 1};
        ts_expect(i32, &stack, expected);

        cspd_stack_clear(&stack);
    }

    /* Edge cases */
    {
        // Edge case: elements leave in last-in, first-out order
        i32        values[] = {1, 4, 7, 9, 2};
        cspd_stack stack    = ts_from(values);

        for (usize i = 5; i > 0; --i) {
            cspd_assert(*(i32 *)cspd_stack_peek(&stack) == values[i - 1]);
            cspd_stack_pop(&stack);
        }

        ts_expect_empty(&stack);

        cspd_stack_clear(&stack);
    }

    {
        // Edge case: one element remaining is both the top and the bottom
        i32        values[] = {1, 2};
        cspd_stack stack    = ts_from(values);

        cspd_stack_pop(&stack);

        i32 expected[] = {1};
        ts_expect(i32, &stack, expected);

        cspd_stack_clear(&stack);
    }

    {
        // Edge case: single element
        i32        values[] = {1};
        cspd_stack stack    = ts_from(values);

        cspd_stack_pop(&stack);

        ts_expect_empty(&stack);

        cspd_stack_clear(&stack);
    }

    {
        // Edge case: stack is reusable after being emptied
        i32        values[] = {1};
        cspd_stack stack    = ts_from(values);

        cspd_stack_pop(&stack);

        i32 data = 3;
        cspd_stack_push(&stack, &data);

        i32 expected[] = {3};
        ts_expect(i32, &stack, expected);

        cspd_stack_clear(&stack);
    }
}

static void test_stack_peek(void)
{
    {
        i32        values[] = {1, 4, 7, 9, 2};
        cspd_stack stack    = ts_from(values);

        //! [Peek]
        void *data = cspd_stack_peek(&stack);

        cspd_assert(*(i32 *)data == 2);
        //! [Peek]

        // Peeking does not modify the stack
        cspd_assert(cspd_stack_peek(&stack) == data);

        i32 expected[] = {2, 9, 7, 4, 1};
        ts_expect(i32, &stack, expected);

        cspd_stack_clear(&stack);
    }

    /* Edge cases */
    {
        // Edge case: single element
        i32        values[] = {1};
        cspd_stack stack    = ts_from(values);

        cspd_assert(*(i32 *)cspd_stack_peek(&stack) == 1);

        cspd_stack_clear(&stack);
    }

    {
        // Edge case: peek follows the top after a pop
        i32        values[] = {1, 4, 7};
        cspd_stack stack    = ts_from(values);

        cspd_stack_pop(&stack);

        cspd_assert(*(i32 *)cspd_stack_peek(&stack) == 4);

        cspd_stack_clear(&stack);
    }
}

static void test_stack_clear(void)
{
    {
        i32        values[] = {1, 4, 7, 9, 2};
        cspd_stack stack    = ts_from(values);

        //! [Clear]
        cspd_stack_clear(&stack);

        cspd_assert(stack.top == NULL);
        cspd_assert(stack.list.head == NULL);
        //! [Clear]
    }

    /* Edge cases */
    {
        // Edge case: empty stack
        cspd_stack stack;
        cspd_stack_init(&stack, sizeof(i32));
        cspd_stack_clear(&stack);

        ts_expect_empty(&stack);
    }

    {
        // Edge case: single element
        i32        values[] = {1};
        cspd_stack stack    = ts_from(values);

        cspd_stack_clear(&stack);

        ts_expect_empty(&stack);
    }

    {
        // Edge case: clearing twice
        i32        values[] = {1, 2, 3};
        cspd_stack stack    = ts_from(values);

        cspd_stack_clear(&stack);
        cspd_stack_clear(&stack);

        ts_expect_empty(&stack);
    }

    {
        // Edge case: stack is reusable after being cleared
        i32        values[] = {1, 2, 3};
        cspd_stack stack    = ts_from(values);

        cspd_stack_clear(&stack);

        i32 data = 4;
        cspd_stack_push(&stack, &data);

        i32 expected[] = {4};
        ts_expect(i32, &stack, expected);

        cspd_stack_clear(&stack);
    }
}

/******************************************************************************
 * Helper Definitions
 *****************************************************************************/

static cspd_stack ts_from_impl(void *values, usize count, usize data_size)
{
    cspd_stack stack;

    cspd_stack_init(&stack, data_size);
    for (usize i = 0; i < count; ++i) {
        cspd_stack_push(&stack, (u8 *)values + i * data_size);
    }

    return stack;
}
