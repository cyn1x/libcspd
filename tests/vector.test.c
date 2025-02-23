#include "vector.test.h"
#include "defs.test.h"
#include <assert.h>
#include <print.h>
#include <stdlib.h>
#include <vector.h>

static void sort_test(void);

vector_t    setup(void)
{
    vector_t vec;
    vector_init(&vec, sizeof(int32));

    //! [Comparator function]
    vec._cmp = &int32_cmp; // Set comparator function pointer
    //! [Comparator function]

    int32 a = 7;
    int32 b = 8;
    int32 c = 7;
    int32 d = 4;
    int32 e = 10;
    int32 f = 3;
    int32 g = 5;

    vector_push(&vec, &a);
    vector_push(&vec, &b);
    vector_push(&vec, &c);
    vector_push(&vec, &d);
    vector_push(&vec, &e);
    vector_push(&vec, &f);
    vector_push(&vec, &g);

    return vec;
}

void vector_test(void)
{
    //! [Initialize]
    vector_t vec;
    vector_init(&vec, sizeof(int32));
    //! [Initialize]

    vec._cmp = &int32_cmp; // Set comparator function pointer

    //! [Push elements]
    int32 w = 3;
    int32 x = 5;
    int32 y = 6;
    int32 z = 1;

    vector_push(&vec, &w);
    vector_push(&vec, &x);
    vector_push(&vec, &y);
    vector_push(&vec, &z);

    // print_vector(int32, &vec);
    // Output: { 3 5 6 1 }

    {
        //! [Get element]
        int32 value;
        int32 e = 5;
        value   = *(int32 *)vector_get(&vec, 1);
        assert(value == e);
        //! [Get element]
    }

    {
        //! [Push elements]
        for (int32 i = 0; i < 8; ++i) {
            int32 k = i;
            vector_push(&vec, &k);
        }

        // print_vector(int32, &vec);
        // Output: { 3 5 6 1 0 1 2 3 4 5 6 7 }

        assert(vec.size == 12);
        int32 value = ((int32 *)vec.data)[10];
        assert(value == 6);
        //! [Push elements]
    }

    {
        //! [Linear search]
        int32  k   = 6;
        size_t idx = vector_lsearch(&vec, &k);
        assert(idx == 2);
        assert(*(int32 *)vec.back == 7);
        //! [Linear search]
    }

    {
        //! [Erasing data]
        vector_erase(&vec, 5, 8);

        // print_vector(int32, &vec);
        // Output: { 3 5 6 1 0 4 5 6 7 }

        int32 value = *(int32 *)vector_get(&vec, 5);
        assert(value == 4);
        assert(*(int32 *)vec.back == 7);
        assert(vec.size == 9);
    }

    vector_erase(&vec, 4, 0);
    // print_vector(int32, &vec);
    // Output: { 0 4 5 6 7 }
    assert(*(int32 *)vec.front == 0);
    assert(*(int32 *)vec.back == 7);
    assert(vec.size == 5);
    //! [Erasing data]

    //! [Inserting data]
    int32 a_vals[] = {1, 2, 3};
    vector_insert(&vec, 1, sizeof(a_vals), &a_vals);
    // print_vector(int32, &vec);
    // Output: { 0 1 2 3 4 5 6 7 }
    assert(*(int32 *)vec.front == 0);

    int32 b_vals[] = {-3, -2, -1};
    vector_insert(&vec, 0, sizeof(b_vals), &b_vals);
    // print_vector(int32, &vec);
    // Output: { -3 -2 -1 0 1 2 3 4 5 6 7 }
    // printf("%d\n", *(int32 *)vec.back);
    // Output: 7
    assert(*(int32 *)vec.front == -3);
    assert(*(int32 *)vec.back == 7);

    int32 c_vals[] = {8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    vector_insert(&vec, 11, sizeof(c_vals), &c_vals);
    // print_vector(int32, &vec);
    // Output: { -3 -2 -1 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 }
    assert(*(int32 *)vec.back == 19);
    //! [Inserting data]

    int32 d_vals[] = {-17, -16, -15, -14, -13, -12, -11,
                      -10, -9,  -8,  -7,  -6,  -5,  -4};
    vector_insert(&vec, 0, sizeof(d_vals), &d_vals);
    // print_vector(int32, &vec);
    // Output: { -17 -16 -15 -14 -13 -12 -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 }
    assert(*(int32 *)vec.front == -17);
    assert(*(int32 *)vec.back == 19);

    vector_pop(&vec);
    assert(*(int32 *)vec.back == 18);

    // Reverse the vector
    vector_reverse(&vec);
    // print_vector(int32, &vec);
    // Output: { 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4 -5
    // -6 -7 -8 -9 -10 -11 -12 -13 -14 -15 -16 -17 }
    assert(*(int32 *)vec.front == 18);
    assert(*(int32 *)vec.back == -17);

    //! [Bubble sort]
    vector_bsort(&vec);
    // print_vector(int32, &vec);
    // Output: { -17 -16 -15 -14 -13 -12 -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 }
    //! [Bubble sort]

    {
        // built-in binary search
        int32   k   = 9;
        size_t *res = bsearch(&k, vec.data, vec.size, vec.data_size, vec._cmp);
        assert(*(int32 *)res == 9);
    }

    {
        //! [Custom binary search]
        int32  n   = -2;
        size_t idx = vector_bsearch(&vec, &n);
        assert(idx == 15);
        //! [Custom binary search]
    }

    int32 key  = 4;
    void *addr = (int32 *)vector_bsearch(&vec, &key);
    // printf("Key found at: %p\n", addr);
    assert(addr != NULL);

    // TODO: Shuffle the items instead
    // Reverse the vector
    vector_reverse(&vec);
    // print_vector(int32, &vec);
    // Output: { 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4 -5
    // -6 -7 -8 -9 -10 -11 -12 -13 -14 -15 -16 -17 }

    sort_test();

    vector_clear(&vec);
    assert(vec.data == NULL);
}

static void sort_test(void)
{
    vector_t vec_a = setup();

    vector_t vec_b;
    vector_t vec_c;
    vector_init(&vec_b, sizeof(int32));
    vector_init(&vec_c, sizeof(int32));

    // Set comparator function pointers
    vec_a._cmp = &int32_cmp;
    vec_b._cmp = &int32_cmp;
    vec_c._cmp = &int32_cmp;

    vector_copy(&vec_b, &vec_a);

    int32 a = 6;
    int32 b = 5;
    int32 c = 3;
    int32 d = 1;
    int32 e = 8;
    int32 f = 7;
    int32 g = 2;
    int32 h = 4;

    vector_push(&vec_c, &a);
    vector_push(&vec_c, &b);
    vector_push(&vec_c, &c);
    vector_push(&vec_c, &d);
    vector_push(&vec_c, &e);
    vector_push(&vec_c, &f);
    vector_push(&vec_c, &g);
    vector_push(&vec_c, &h);

    // print_vector(int32, &vec_a);
    // Output: { 7 8 7 4 10 3 5 }

    // built-in quicksort
    qsort(vec_a.data, vec_a.size, vec_a.data_size, vec_a._cmp);

    // print_vector(int32, &vec_a);
    // Output: { 3 4 5 7 7 8 10 }

    assert(*(int32 *)vec_a.front == 3);
    assert(*(int32 *)vec_a.back == 10);

    // print_vector(int32, &vec_b);
    // Output: { 7 8 7 4 10 3 5 }

    vector_qsort(&vec_b, 0, vec_b.size - 1);
    // print_vector(int32, &vec_b);
    // Output: { 3 4 5 7 7 8 10 }

    assert(*(int32 *)vec_b.front == 3);
    assert(*(int32 *)vec_b.back == 10);

    // print_vector(int32, &vec_c);
    // Output: { 1 2 3 4 5 6 7 8 }

    vector_msort(&vec_c, vec_c.size, int32_cmp);
    // print_vector(int32, &vec_c);
    // Output: { 1 2 3 4 5 6 7 8 }

    for (size_t i = 0; i < vec_c.size - 1; i++) {
        assert(*(int32 *)vector_get(&vec_c, i) <=
               *(int32 *)vector_get(&vec_c, i + 1));
    }

    vector_clear(&vec_a);
    vector_clear(&vec_b);
    vector_clear(&vec_c);
    assert(vec_a.data == NULL);
    assert(vec_b.data == NULL);
    assert(vec_c.data == NULL);
}
