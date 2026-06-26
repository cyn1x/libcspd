#include "cspd_vector.test.h"
#include "cspd_defs.test.h"
#include <assert.h>
#include <cspd_print.h>
#include <cspd_vector.h>
#include <stdlib.h>

static void        sort_test(void);

static cspd_vector setup(void)
{
    cspd_vector vec;
    cspd_vector_init(&vec, sizeof(i32));

    i32 a = 7;
    i32 b = 8;
    i32 c = 7;
    i32 d = 4;
    i32 e = 10;
    i32 f = 3;
    i32 g = 5;

    cspd_vector_push(&vec, &a);
    cspd_vector_push(&vec, &b);
    cspd_vector_push(&vec, &c);
    cspd_vector_push(&vec, &d);
    cspd_vector_push(&vec, &e);
    cspd_vector_push(&vec, &f);
    cspd_vector_push(&vec, &g);

    return vec;
}

void cspd_vector_test(void)
{
    //! [Initialize]
    cspd_vector vec;
    cspd_vector_init(&vec, sizeof(i32));
    //! [Initialize]

    //! [Push elements]
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

    {
        //! [Get element]
        i32 value;
        i32 e = 5;
        value = *(i32 *)cspd_vector_get(&vec, 1);
        assert(value == e);
        //! [Get element]
    }

    {
        //! [Push elements]
        for (i32 i = 0; i < 8; ++i) {
            i32 k = i;
            cspd_vector_push(&vec, &k);
        }

        // cspd_print_vector(i32, &vec);
        // Output: { 3 5 6 1 0 1 2 3 4 5 6 7 }

        assert(vec.size == 12);
        i32 value = ((i32 *)vec.data)[10];
        assert(value == 6);
        //! [Push elements]
    }

    {
        //! [Linear search]
        i32    k   = 6;
        size_t idx = cspd_vector_lsearch(&vec, &k);
        assert(idx == 2);
        assert(*(i32 *)cspd_vector_back(&vec) == 7);
        //! [Linear search]
    }

    {
        //! [Erasing data]
        cspd_vector_erase(&vec, 5, 8);

        // cspd_print_vector(i32, &vec);
        // Output: { 3 5 6 1 0 4 5 6 7 }

        i32 value = *(i32 *)cspd_vector_get(&vec, 5);
        assert(value == 4);
        assert(*(i32 *)cspd_vector_front(&vec) == 3);
        assert(vec.size == 9);
    }

    cspd_vector_erase(&vec, 4, 0);
    // cspd_print_vector(i32, &vec);
    // Output: { 0 4 5 6 7 }
    assert(*(i32 *)cspd_vector_front(&vec) == 0);
    assert(*(i32 *)cspd_vector_back(&vec) == 7);
    assert(vec.size == 5);
    //! [Erasing data]

    //! [Inserting data]
    i32 a_vals[] = {1, 2, 3};
    cspd_vector_insert(&vec, 1, sizeof(a_vals), &a_vals);
    // cspd_print_vector(i32, &vec);
    // Output: { 0 1 2 3 4 5 6 7 }
    assert(*(i32 *)cspd_vector_front(&vec) == 0);

    i32 b_vals[] = {-3, -2, -1};
    cspd_vector_insert(&vec, 0, sizeof(b_vals), &b_vals);
    // cspd_print_vector(i32, &vec);
    // Output: { -3 -2 -1 0 1 2 3 4 5 6 7 }
    // printf("%d\n", *(i32 *)vec.back);
    // Output: 7
    assert(*(i32 *)cspd_vector_front(&vec) == -3);
    assert(*(i32 *)cspd_vector_back(&vec) == 7);

    i32 c_vals[] = {8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    cspd_vector_insert(&vec, 11, sizeof(c_vals), &c_vals);
    // cspd_print_vector(i32, &vec);
    // Output: { -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 }
    assert(*(i32 *)cspd_vector_back(&vec) == 19);
    //! [Inserting data]

    i32 d_vals[] = {-17, -16, -15, -14, -13, -12, -11,
                    -10, -9,  -8,  -7,  -6,  -5,  -4};
    cspd_vector_insert(&vec, 0, sizeof(d_vals), &d_vals);
    // cspd_print_vector(i32, &vec);
    // Output: { -17 -16 -15 -14 -13 -12 -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 }
    assert(*(i32 *)cspd_vector_front(&vec) == -17);
    assert(*(i32 *)cspd_vector_back(&vec) == 19);

    cspd_vector_pop(&vec);
    assert(*(i32 *)cspd_vector_back(&vec) == 18);

    // Reverse the vector
    cspd_vector_reverse(&vec);
    // cspd_print_vector(i32, &vec);
    // Output: { 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4 -5
    // -6 -7 -8 -9 -10 -11 -12 -13 -14 -15 -16 -17 }
    assert(*(i32 *)cspd_vector_front(&vec) == 18);
    assert(*(i32 *)cspd_vector_back(&vec) == -17);

    //! [Bubble sort]
    cspd_vector_bsort(&vec, i32_cmp);
    // cspd_print_vector(i32, &vec);
    // Output: { -17 -16 -15 -14 -13 -12 -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 }
    //! [Bubble sort]

    {
        // built-in binary search
        i32     k   = 9;
        size_t *res = bsearch(&k, vec.data, vec.size, vec.data_size, i32_cmp);
        assert(*(i32 *)res == 9);
    }

    {
        //! [Custom binary search]
        i32    n   = -2;
        size_t idx = cspd_vector_bsearch(&vec, &n, i32_cmp);
        assert(idx == 15);
        //! [Custom binary search]
    }

    i32   key  = 4;
    void *addr = (i32 *)cspd_vector_bsearch(&vec, &key, i32_cmp);
    // printf("Key found at: %p\n", addr);
    assert(addr != NULL);

    // TODO: Shuffle the items instead
    // Reverse the vector
    cspd_vector_reverse(&vec);
    // cspd_print_vector(i32, &vec);
    // Output: { 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4 -5
    // -6 -7 -8 -9 -10 -11 -12 -13 -14 -15 -16 -17 }

    sort_test();

    cspd_vector_clear(&vec);
    assert(vec.data == NULL);
}

static void sort_test(void)
{
    cspd_vector vec_a = setup();

    cspd_vector vec_b;
    cspd_vector vec_c;
    cspd_vector_init(&vec_b, sizeof(i32));
    cspd_vector_init(&vec_c, sizeof(i32));

    cspd_vector_copy(&vec_b, &vec_a);

    i32 a = 6;
    i32 b = 5;
    i32 c = 3;
    i32 d = 1;
    i32 e = 8;
    i32 f = 7;
    i32 g = 2;
    i32 h = 4;

    cspd_vector_push(&vec_c, &a);
    cspd_vector_push(&vec_c, &b);
    cspd_vector_push(&vec_c, &c);
    cspd_vector_push(&vec_c, &d);
    cspd_vector_push(&vec_c, &e);
    cspd_vector_push(&vec_c, &f);
    cspd_vector_push(&vec_c, &g);
    cspd_vector_push(&vec_c, &h);

    // cspd_print_vector(i32, &vec_a);
    // Output: { 7 8 7 4 10 3 5 }

    // built-in quicksort
    qsort(vec_a.data, vec_a.size, vec_a.data_size, i32_cmp);

    // cspd_print_vector(i32, &vec_a);
    // Output: { 3 4 5 7 7 8 10 }

    assert(*(i32 *)cspd_vector_front(&vec_a) == 3);
    assert(*(i32 *)cspd_vector_back(&vec_a) == 10);

    // cspd_print_vector(i32, &vec_b);
    // Output: { 7 8 7 4 10 3 5 }

    cspd_vector_qsort(&vec_b, 0, vec_b.size - 1, i32_cmp);
    // cspd_print_vector(i32, &vec_b);
    // Output: { 3 4 5 7 7 8 10 }

    assert(*(i32 *)cspd_vector_front(&vec_a) == 3);
    assert(*(i32 *)cspd_vector_back(&vec_b) == 10);

    // cspd_print_vector(i32, &vec_c);
    // Output: { 1 2 3 4 5 6 7 8 }

    cspd_vector_msort(&vec_c, vec_c.size, i32_cmp);
    // cspd_print_vector(i32, &vec_c);
    // Output: { 1 2 3 4 5 6 7 8 }

    for (size_t i = 0; i < vec_c.size - 1; i++) {
        assert(*(i32 *)cspd_vector_get(&vec_c, i) <=
               *(i32 *)cspd_vector_get(&vec_c, i + 1));
    }

    cspd_vector_clear(&vec_a);
    cspd_vector_clear(&vec_b);
    cspd_vector_clear(&vec_c);
    assert(vec_a.data == NULL);
    assert(vec_b.data == NULL);
    assert(vec_c.data == NULL);
}
