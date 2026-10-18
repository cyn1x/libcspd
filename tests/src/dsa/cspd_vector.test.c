#include "cspd_vector.test.h"
#include "cspd_cmp.test.h"
#include <cspd_assert.h>
#include <cspd_print.h>
#include <cspd_types.h>
#include <cspd_vector.h>

/******************************************************************************
 * Helper Declarations
 *****************************************************************************/
#define tv_from(ARR)                                                           \
    tv_from_impl((ARR), sizeof(ARR) / sizeof((ARR)[0]), sizeof((ARR)[0]))

#define tv_expect(TYPE, VEC, ARR)                                              \
    do {                                                                       \
        const cspd_vector *_v = (VEC);                                         \
        const TYPE        *_e = (ARR);                                         \
        usize              _n = sizeof(ARR) / sizeof((ARR)[0]);                \
                                                                               \
        cspd_assert(_v->data_size == sizeof(TYPE));                            \
        cspd_assert(_v->size == _n);                                           \
        for (usize _i = 0; _i < _n; ++_i) {                                    \
            cspd_assert(*(TYPE *)cspd_vector_get(_v, _i) == _e[_i]);           \
        }                                                                      \
    } while (0)

static cspd_vector tv_from_impl(const void *values, usize count,
                                usize data_size);

/******************************************************************************
 * Test Declarations
 *****************************************************************************/
static void        test_vec_init(void);
static void        test_vec_push(void);
static void        test_vec_addrange(void);
static void        test_vec_insert(void);
static void        test_vec_erase(void);
static void        test_vec_clear(void);
static void        test_vec_copy(void);
static void        test_vec_reverse(void);
static void        test_vec_lsearch(void);
static void        test_vec_bsearch(void);
static void        test_vec_bsort(void);
static void        test_vec_qsort(void);
static void        test_vec_msort(void);
static void        test_vec_get(void);
static void        test_vec_back(void);
static void        test_vec_front(void);
static void        test_vec_pop(void);

/******************************************************************************
 * Test Runner
 *****************************************************************************/
void               cspd_vector_test(void)
{
    test_vec_init();
    test_vec_push();
    test_vec_addrange();
    test_vec_insert();
    test_vec_erase();
    test_vec_clear();
    test_vec_copy();
    test_vec_reverse();
    test_vec_lsearch();
    test_vec_bsearch();
    test_vec_bsort();
    test_vec_qsort();
    test_vec_msort();
    test_vec_get();
    test_vec_back();
    test_vec_front();
    test_vec_pop();
}

/******************************************************************************
 * Test Definitions
 *****************************************************************************/

static void test_vec_init(void)
{
    //! [Initialize vector]
    cspd_vector vec;
    cspd_vector_init(&vec, sizeof(i32));

    // cspd_print_vector(i32, &vec);
    // Output: { }

    cspd_assert(vec.capacity == 32 && vec.size == 0 && vec.data != NULL);
    //! [Initialize vector]

    cspd_vector_clear(&vec);
}

static void test_vec_push(void)
{
    //! [Push elements]
    cspd_vector vec;
    cspd_vector_init(&vec, sizeof(i32));

    i32 w = 3;
    i32 x = 5;
    i32 y = 6;
    i32 z = 1;

    cspd_vector_push(&vec, &w);
    cspd_vector_push(&vec, &x);
    cspd_vector_push(&vec, &y);
    cspd_vector_push(&vec, &z);

    // cspd_print_vector(i32, &vec);
    // Output: { 3 5 6 1 }

    for (i32 i = 0; i < 8; ++i) {
        cspd_vector_push(&vec, &i);
    }

    // cspd_print_vector(i32, &vec);
    // Output: { 3 5 6 1 0 1 2 3 4 5 6 7 }

    cspd_assert(vec.capacity == 32);
    cspd_assert(vec.size == 12);
    cspd_assert(((i32 *)vec.data)[10] == 6);
    //! [Push elements]

    cspd_vector_clear(&vec);
}

static void test_vec_addrange(void)
{
    i32         values[] = {3, 5, 6, 1};
    cspd_vector vec      = tv_from(values);
    //! [Add range]
    // cspd_print_vector(i32, &vec);
    // Output: { 3 5 6 1 }

    i32         data[] = {8, 7, 4, 2};
    cspd_vector_addrange(&vec, sizeof(data), data);

    // cspd_print_vector(i32, &vec);
    // Output: { 3 5 6 1 8 7 4 2 }

    cspd_assert(vec.capacity == 32);
    cspd_assert(vec.size == 8);
    //! [Add range]

    cspd_vector_clear(&vec);
}

static void test_vec_insert(void)
{
    {
        i32         values[] = {0, 1, 2, 5, 6, 7, 8, 9};
        cspd_vector vec      = tv_from(values);

        //! [Inserting elements]
        // cspd_print_vector(i32, &vec);
        // Output: { 0 1 4 5 6 7 8 9 }

        i32         data[] = {3, 4};
        cspd_vector_insert(&vec, 3, sizeof(data), data);

        // cspd_print_vector(i32, &vec);
        // Output: { 0 1 2 3 4 5 6 7 8 9 }
        //! [Inserting elements]

        i32 expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        tv_expect(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    /* Edge cases */
    {
        // Edge case: front
        i32         values[] = {0, 1, 2};
        cspd_vector vec      = tv_from(values);

        i32         b[]      = {-3, -2, -1};
        cspd_vector_insert(&vec, 0, sizeof(b), b);

        i32 expected[] = {-3, -2, -1, 0, 1, 2};
        tv_expect(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    {
        // Edge case: back
        i32         values[] = {0, 1, 2};
        cspd_vector vec      = tv_from(values);

        i32         c[]      = {3, 4, 5};
        cspd_vector_insert(&vec, 3, sizeof(c), c);

        i32 expected[] = {0, 1, 2, 3, 4, 5};
        tv_expect(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    {
        // Edge case: empty vector
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(i32));

        i32 d[] = {7, 8};
        cspd_vector_insert(&vec, 0, sizeof(d), d);

        i32 expected[] = {7, 8};
        tv_expect(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }
}

static void test_vec_erase(void)
{
    {
        i32         values[] = {3, 5, 6, 1, 0, 8, 7, 4, 2};
        cspd_vector vec      = tv_from(values);

        //! [Erasing elements]
        // cspd_print_vector(i32, &vec);
        // Output: { 3 5 6 1 0 8 7 4 2 }

        cspd_vector_erase(&vec, 5, 8);

        // cspd_print_vector(i32, &vec);
        // Output: { 3 5 6 1 0 }

        cspd_assert(vec.size == 5);
        //! [Erasing elements]

        i32 expected[] = {3, 5, 6, 1, 0};
        tv_expect(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    /* Edge cases */
    {
        // Edge case: single element
        i32         values[] = {3, 5, 6, 1};
        cspd_vector vec      = tv_from(values);

        // cspd_print_vector(i32, &vec);
        // Output: { 3 5 6 1 }

        cspd_vector_erase(&vec, 0, 0);

        // cspd_print_vector(i32, &vec);
        // Output: { 5 6 1 }

        cspd_assert(vec.size == 3);
        cspd_assert(*(i32 *)cspd_vector_front(&vec) == 5);
        cspd_assert(*(i32 *)cspd_vector_get(&vec, 1) == 6);
        cspd_assert(*(i32 *)cspd_vector_back(&vec) == 1);

        cspd_vector_clear(&vec);
    }

    {
        // Edge case: reversed range
        i32         values[] = {3, 5, 6, 1, 0, 5, 6, 7};
        cspd_vector vec      = tv_from(values);

        // cspd_print_vector(i32, &vec);
        // Output: { 3 5 6 1 0 5 6 7 }

        cspd_vector_erase(&vec, 4, 0);

        // cspd_print_vector(i32, &vec);
        // Output: { 5 6 7 }

        cspd_assert(vec.size == 3);
        cspd_assert(*(i32 *)cspd_vector_get(&vec, 1) == 6);
        cspd_assert(*(i32 *)cspd_vector_front(&vec) == 5);
        cspd_assert(*(i32 *)cspd_vector_back(&vec) == 7);

        cspd_vector_clear(&vec);
    }

    {
        // Edge case: whole vector
        i32         values[] = {3, 5, 6, 1};
        cspd_vector vec      = tv_from(values);

        // cspd_print_vector(i32, &vec);
        // Output: { 3 5 6 1 }

        cspd_vector_erase(&vec, 0, 3);

        // cspd_print_vector(i32, &vec);
        // Output: { }

        cspd_assert(vec.size == 0);

        cspd_vector_clear(&vec);
    }
}

static void test_vec_clear(void)
{
    {
        //! [Delete vector]
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(i32));

        for (usize i = 0; i < 10; ++i) {
            cspd_vector_push(&vec, &i);
        }

        cspd_vector_clear(&vec);

        cspd_assert(vec.size == 0);
        cspd_assert(vec.capacity == 0);
        cspd_assert(vec.data == NULL);
        //! [Delete vector]
    }

    {
        // Edge case: empty vector
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(i32));
        cspd_vector_clear(&vec);
    }
}

static void test_vec_copy(void)
{
    i32         values[] = {3, 5, 6, 1, 0, 1, 2, 3};
    cspd_vector vec_a    = tv_from(values);

    // cspd_print_vector(i32, &vec_a);
    // Output: { 3 5 6 1 0 1 2 3 }

    cspd_vector vec_b;
    cspd_vector_init(&vec_b, sizeof(i32));
    cspd_vector_copy(&vec_a, &vec_b);

    // cspd_print_vector(i32, &vec_a);
    // Output: { 3 5 6 1 0 1 2 3 }

    cspd_vector_clear(&vec_a);
    cspd_vector_clear(&vec_b);
}

static void test_vec_reverse(void)
{
    i32         values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cspd_vector vec      = tv_from(values);

    // cspd_print_vector(i32, &vec);
    // Output: { 1 2 3 4 5 6 7 8 9 }

    cspd_vector_reverse(&vec);

    // cspd_print_vector(i32, &vec);
    // Output: { 9 8 7 6 5 4 3 2 1 }

    i32 expected[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    tv_expect(i32, &vec, expected);

    cspd_vector_clear(&vec);
}

static void test_vec_lsearch(void)
{
    i32         values[] = {3, 5, 6, 1, 0, 1, 2, 3};
    cspd_vector vec      = tv_from(values);

    //! [Linear search]
    // cspd_print_vector(i32, &vec);
    // Output: { 3 5 6 1 0 1 2 3 }

    i32         key = 6;
    usize       idx = cspd_vector_lsearch(&vec, &key);

    cspd_assert(idx == 2);
    //! [Linear search]

    cspd_vector_clear(&vec);
}

static void test_vec_bsearch(void)
{
    i32         values[] = {3, 5, 6, 1, 0, 1, 2, 3};
    cspd_vector vec      = tv_from(values);

    //! [Binary search]
    // cspd_print_vector(i32, &vec);
    // Output: { 3 5 6 1 0 1 2 3 }

    // Sort the vector before using binary search
    cspd_vector_qsort(&vec, 0, vec.size - 1, i32_cmp);

    // cspd_print_vector(i32, &vec);
    // Output: { 0 1 1 2 3 3 5 6 }

    i32   key = 5;
    usize idx = cspd_vector_bsearch(&vec, &key, i32_cmp);
    cspd_assert(idx == 6);
    //! [Binary search]

    cspd_vector_clear(&vec);

    /* Edge cases */
    {
        // Edge case: unsorted vector
        i32         values[] = {3, 5, 6, 1, 0, 1, 2, 3};
        cspd_vector vec      = tv_from(values);

        // cspd_print_vector(i32, &vec);
        // Output: { 3 5 6 1 0 1 2 3 }

        i32         key = 6;
        usize       idx = cspd_vector_bsearch(&vec, &key, i32_cmp);
        cspd_assert(idx == SIZE_MAX);

        cspd_vector_clear(&vec);
    }
}

static void test_vec_bsort(void)
{
    i32         values[] = {15, 3, 8, 0, 4, 11, 6, 12, 1, 7};
    cspd_vector vec      = tv_from(values);

    //! [Bubble sort]
    // cspd_print_vector(i32, &vec);
    // Output: { 15 3 8 0 4 11 6 12 1 7 }

    cspd_vector_bsort(&vec, i32_cmp);

    // cspd_print_vector(i32, &vec);
    // Output: { 0 1 3 4 6 7 8 11 12 15 }
    //! [Bubble sort]

    i32 expected[] = {0, 1, 3, 4, 6, 7, 8, 11, 12, 15};
    tv_expect(i32, &vec, expected);

    cspd_vector_clear(&vec);
}

static void test_vec_qsort(void)
{
    i32         values[] = {7, 8, 7, 4, 10, 3, 5};
    cspd_vector vec      = tv_from(values);

    //! [Quick sort]
    // cspd_print_vector(i32, &vec);
    // Output: { 7 8 7 4 10 3 5 }

    cspd_vector_qsort(&vec, 0, vec.size - 1, i32_cmp);

    // cspd_print_vector(i32, &vec);
    // Output: { 7 8 7 4 10 3 5 }
    //! [Quick sort]

    i32 expected[] = {3, 4, 5, 7, 7, 8, 10};
    tv_expect(i32, &vec, expected);

    cspd_vector_clear(&vec);
}

static void test_vec_msort(void)
{
    i32         values[] = {7, 8, 7, 4, 10, 3, 5};
    cspd_vector vec      = tv_from(values);

    //! [Merge sort]
    // cspd_print_vector(i32, &vec);
    // Output: { 7 8 7 4 10 3 5 }

    cspd_vector_msort(&vec, vec.size, i32_cmp);

    // cspd_print_vector(i32, &vec);
    // Output: { 3 4 5 7 7 8 10 }
    //! [Merge sort]

    i32 expected[] = {3, 4, 5, 7, 7, 8, 10};
    tv_expect(i32, &vec, expected);

    cspd_vector_clear(&vec);
}

static void test_vec_get(void)
{
    i32         values[] = {7, 8, 7, 4, 10, 3, 5};
    cspd_vector vec      = tv_from(values);

    //! [Get element]
    // cspd_print_vector(i32, &vec);
    // Output: { 7 8 7 4 10 3 5 }

    cspd_assert(*(i32 *)cspd_vector_get(&vec, 0) == 7);
    cspd_assert(*(i32 *)cspd_vector_back(&vec) == 5);
    //! [Get element]

    cspd_vector_clear(&vec);
}

static void test_vec_back(void)
{
    i32         values[] = {1, 2, 3};
    cspd_vector vec      = tv_from(values);

    // cspd_print_vector(i32, &vec);
    // Output: { 1 2 3 }

    cspd_assert(*(i32 *)cspd_vector_back(&vec) == 3);

    cspd_vector_clear(&vec);
}

static void test_vec_front(void)
{
    i32         values[] = {1, 2, 3};
    cspd_vector vec      = tv_from(values);

    // cspd_print_vector(i32, &vec);
    // Output: { 1 2 3 }

    cspd_assert(*(i32 *)cspd_vector_front(&vec) == 1);

    cspd_vector_clear(&vec);
}

static void test_vec_pop(void)
{
    {
        i32         values[] = {1, 2, 3};
        cspd_vector vec      = tv_from(values);

        //! [Pop element]
        // cspd_print_vector(i32, &vec);
        // Output: { 1 2 3 }

        cspd_vector_pop(&vec);

        cspd_assert(*(i32 *)cspd_vector_front(&vec) == 1);
        cspd_assert(*(i32 *)cspd_vector_back(&vec) == 2);
        //! [Pop element]

        cspd_vector_clear(&vec);
    }

    /* Edge cases */
    {
        // Edge case: whole vector
        i32         values[] = {3, 2, 1};
        cspd_vector vec      = tv_from(values);

        cspd_vector_pop(&vec);
        cspd_vector_pop(&vec);
        cspd_vector_pop(&vec);

        cspd_assert(vec.size == 0);
        cspd_assert(vec.capacity == 32);

        cspd_vector_clear(&vec);
    }

    {
        // Edge case: empty vector
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(i32));
        cspd_vector_pop(&vec);

        cspd_assert(vec.size == 0);

        cspd_vector_clear(&vec);
    }
}

/******************************************************************************
 * Helper Definitions
 *****************************************************************************/

static cspd_vector tv_from_impl(const void *values, usize count,
                                usize data_size)
{
    cspd_vector vec;

    cspd_vector_init(&vec, data_size);
    cspd_vector_addrange(&vec, count * data_size, values);

    return vec;
}
