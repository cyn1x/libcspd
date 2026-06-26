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
    cspd_vector_init(&vec, sizeof(int32));

    int32 a = 7;
    int32 b = 8;
    int32 c = 7;
    int32 d = 4;
    int32 e = 10;
    int32 f = 3;
    int32 g = 5;

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
    cspd_vector_init(&vec, sizeof(int32));
    //! [Initialize]

    //! [Push elements]
    int32 w = 3;
    int32 x = 5;
    int32 y = 6;
    int32 z = 1;

    cspd_vector_push(&vec, &w);
    cspd_vector_push(&vec, &x);
    cspd_vector_push(&vec, &y);
    cspd_vector_push(&vec, &z);

    // cspd_print_vector(int32, &vec);
    // Output: { 3 5 6 1 }

    {
        //! [Get element]
        int32 value;
        int32 e = 5;
        value   = *(int32 *)cspd_vector_get(&vec, 1);
        assert(value == e);
        //! [Get element]
    }

    {
        //! [Push elements]
        for (int32 i = 0; i < 8; ++i) {
            int32 k = i;
            cspd_vector_push(&vec, &k);
        }

        // cspd_print_vector(int32, &vec);
        // Output: { 3 5 6 1 0 1 2 3 4 5 6 7 }

        assert(vec.size == 12);
        int32 value = ((int32 *)vec.data)[10];
        assert(value == 6);
        //! [Push elements]
    }

    {
        //! [Linear search]
        int32  k   = 6;
        size_t idx = cspd_vector_lsearch(&vec, &k);
        assert(idx == 2);
        assert(*(int32 *)cspd_vector_back(&vec) == 7);
        //! [Linear search]
    }

    {
        //! [Erasing data]
        cspd_vector_erase(&vec, 5, 8);

        // cspd_print_vector(int32, &vec);
        // Output: { 3 5 6 1 0 4 5 6 7 }

        int32 value = *(int32 *)cspd_vector_get(&vec, 5);
        assert(value == 4);
        assert(*(int32 *)cspd_vector_front(&vec) == 3);
        assert(vec.size == 9);
    }

    cspd_vector_erase(&vec, 4, 0);
    // cspd_print_vector(int32, &vec);
    // Output: { 0 4 5 6 7 }
    assert(*(int32 *)cspd_vector_front(&vec) == 0);
    assert(*(int32 *)cspd_vector_back(&vec) == 7);
    assert(vec.size == 5);
    //! [Erasing data]

    //! [Inserting data]
    int32 a_vals[] = {1, 2, 3};
    cspd_vector_insert(&vec, 1, sizeof(a_vals), &a_vals);
    // cspd_print_vector(int32, &vec);
    // Output: { 0 1 2 3 4 5 6 7 }
    assert(*(int32 *)cspd_vector_front(&vec) == 0);

    int32 b_vals[] = {-3, -2, -1};
    cspd_vector_insert(&vec, 0, sizeof(b_vals), &b_vals);
    // cspd_print_vector(int32, &vec);
    // Output: { -3 -2 -1 0 1 2 3 4 5 6 7 }
    // printf("%d\n", *(int32 *)vec.back);
    // Output: 7
    assert(*(int32 *)cspd_vector_front(&vec) == -3);
    assert(*(int32 *)cspd_vector_back(&vec) == 7);

    int32 c_vals[] = {8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    cspd_vector_insert(&vec, 11, sizeof(c_vals), &c_vals);
    // cspd_print_vector(int32, &vec);
    // Output: { -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 }
    assert(*(int32 *)cspd_vector_back(&vec) == 19);
    //! [Inserting data]

    int32 d_vals[] = {-17, -16, -15, -14, -13, -12, -11,
                      -10, -9,  -8,  -7,  -6,  -5,  -4};
    cspd_vector_insert(&vec, 0, sizeof(d_vals), &d_vals);
    // cspd_print_vector(int32, &vec);
    // Output: { -17 -16 -15 -14 -13 -12 -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 }
    assert(*(int32 *)cspd_vector_front(&vec) == -17);
    assert(*(int32 *)cspd_vector_back(&vec) == 19);

    cspd_vector_pop(&vec);
    assert(*(int32 *)cspd_vector_back(&vec) == 18);

    // Reverse the vector
    cspd_vector_reverse(&vec);
    // cspd_print_vector(int32, &vec);
    // Output: { 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4 -5
    // -6 -7 -8 -9 -10 -11 -12 -13 -14 -15 -16 -17 }
    assert(*(int32 *)cspd_vector_front(&vec) == 18);
    assert(*(int32 *)cspd_vector_back(&vec) == -17);

    //! [Bubble sort]
    cspd_vector_bsort(&vec, int32_cmp);
    // cspd_print_vector(int32, &vec);
    // Output: { -17 -16 -15 -14 -13 -12 -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 }
    //! [Bubble sort]

    {
        // built-in binary search
        int32   k   = 9;
        size_t *res = bsearch(&k, vec.data, vec.size, vec.data_size, int32_cmp);
        assert(*(int32 *)res == 9);
    }

    {
        //! [Custom binary search]
        int32  n   = -2;
        size_t idx = cspd_vector_bsearch(&vec, &n, int32_cmp);
        assert(idx == 15);
        //! [Custom binary search]
    }

    int32 key  = 4;
    void *addr = (int32 *)cspd_vector_bsearch(&vec, &key, int32_cmp);
    // printf("Key found at: %p\n", addr);
    assert(addr != NULL);

    // TODO: Shuffle the items instead
    // Reverse the vector
    cspd_vector_reverse(&vec);
    // cspd_print_vector(int32, &vec);
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
    cspd_vector_init(&vec_b, sizeof(int32));
    cspd_vector_init(&vec_c, sizeof(int32));

    cspd_vector_copy(&vec_b, &vec_a);

    int32 a = 6;
    int32 b = 5;
    int32 c = 3;
    int32 d = 1;
    int32 e = 8;
    int32 f = 7;
    int32 g = 2;
    int32 h = 4;

    cspd_vector_push(&vec_c, &a);
    cspd_vector_push(&vec_c, &b);
    cspd_vector_push(&vec_c, &c);
    cspd_vector_push(&vec_c, &d);
    cspd_vector_push(&vec_c, &e);
    cspd_vector_push(&vec_c, &f);
    cspd_vector_push(&vec_c, &g);
    cspd_vector_push(&vec_c, &h);

    // cspd_print_vector(int32, &vec_a);
    // Output: { 7 8 7 4 10 3 5 }

    // built-in quicksort
    qsort(vec_a.data, vec_a.size, vec_a.data_size, int32_cmp);

    // cspd_print_vector(int32, &vec_a);
    // Output: { 3 4 5 7 7 8 10 }

    assert(*(int32 *)cspd_vector_front(&vec_a) == 3);
    assert(*(int32 *)cspd_vector_back(&vec_a) == 10);

    // cspd_print_vector(int32, &vec_b);
    // Output: { 7 8 7 4 10 3 5 }

    cspd_vector_qsort(&vec_b, 0, vec_b.size - 1, int32_cmp);
    // cspd_print_vector(int32, &vec_b);
    // Output: { 3 4 5 7 7 8 10 }

    assert(*(int32 *)cspd_vector_front(&vec_a) == 3);
    assert(*(int32 *)cspd_vector_back(&vec_b) == 10);

    // cspd_print_vector(int32, &vec_c);
    // Output: { 1 2 3 4 5 6 7 8 }

    cspd_vector_msort(&vec_c, vec_c.size, int32_cmp);
    // cspd_print_vector(int32, &vec_c);
    // Output: { 1 2 3 4 5 6 7 8 }

    for (size_t i = 0; i < vec_c.size - 1; i++) {
        assert(*(int32 *)cspd_vector_get(&vec_c, i) <=
               *(int32 *)cspd_vector_get(&vec_c, i + 1));
    }

    cspd_vector_clear(&vec_a);
    cspd_vector_clear(&vec_b);
    cspd_vector_clear(&vec_c);
    assert(vec_a.data == NULL);
    assert(vec_b.data == NULL);
    assert(vec_c.data == NULL);
}
