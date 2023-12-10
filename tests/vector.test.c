#include "vector.test.h"
#include "vector.h"

void print_vector(vector *vec)
{
    printf("{ ");
    for (size_t i = 0; i != vec->size; ++i) {
        printf("%d ", *(int32 *)vector_get(vec, i));
    }
    printf("} \n");
}

void vector_test(void)
{
    //! [Initialize]
    int32  value;
    vector vec;
    vector_init(&vec, sizeof(int32));
    //! [Initialize]

    //! [Push elements]
    int32 w = 3;
    int32 x = 5;
    int32 y = 6;
    int32 z = 1;

    vector_push(&vec, &w);
    vector_push(&vec, &x);
    vector_push(&vec, &y);
    vector_push(&vec, &z);
    // print_vector(&vec);
    // Output: { 3, 5, 6, 1 }
    //! [Push elements]

    //! [Get element]
    int32 e = 5;
    value   = *(int32 *)vector_get(&vec, 1);
    assert(value == e);
    //! [Get element]

    for (int32 i = 0; i < 8; ++i) {
        int32 k = i;
        vector_push(&vec, &k);
    }
    // print_vector(&vec);
    // Output: { 3, 5, 6, 1, 0, 1, 2, 3, 4, 5, 6, 7 }
    value = ((int32 *)vec.data)[10];
    assert(value == 6);

    //! [Linear search]
    int32  k   = 6;
    size_t idx = vector_lsearch(&vec, &k);
    assert(idx == 2);
    assert(*(int32 *)vec.back == 7);
    //! [Linear search]

    //! [Erasing data]
    vector_erase(&vec, 5, 8);
    // print_vector(&vec);
    // Output: { 3, 5, 6, 1, 0, 4, 5, 6, 7 }
    value = *(int32 *)vector_get(&vec, 5);
    assert(value == 4);
    assert(*(int32 *)vec.back == 7);
    assert(vec.size == 9);

    vector_erase(&vec, 4, 0);
    // print_vector(&vec);
    // Output: { 0, 4, 5, 6, 7 }
    assert(*(int32 *)vec.front == 0);
    assert(*(int32 *)vec.back == 7);
    assert(vec.size == 5);
    //! [Erasing data]

    //! [Inserting data]
    int32 a_vals[] = {1, 2, 3};
    vector_insert(&vec, 1, sizeof(a_vals), &a_vals);
    // print_vector(&vec);
    // Output: { 0, 1, 2, 3, 4, 5, 6, 7 }
    assert(*(int32 *)vec.front == 0);

    int32 b_vals[] = {-3, -2, -1};
    vector_insert(&vec, 0, sizeof(b_vals), &b_vals);
    // print_vector(&vec);
    // Output: { -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7 }
    // printf("%d\n", *(int32 *)vec.back);
    // Output: 7
    assert(*(int32 *)vec.front == -3);
    assert(*(int32 *)vec.back == 7);

    int32 c_vals[] = {8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    vector_insert(&vec, 11, sizeof(c_vals), &c_vals);
    // print_vector(&vec);
    // Output: { -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    // 15, 16, 17, 18, 19 }
    assert(*(int32 *)vec.back == 19);
    //! [Inserting data]

    int32 d_vals[] = {-17, -16, -15, -14, -13, -12, -11,
                      -10, -9,  -8,  -7,  -6,  -5,  -4};
    vector_insert(&vec, 0, sizeof(d_vals), &d_vals);
    // print_vector(&vec);
    // Output:{ -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4,
    // -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    // 18, 19 }
    assert(*(int32 *)vec.front == -17);
    assert(*(int32 *)vec.back == 19);

    vector_pop(&vec);
    assert(*(int32 *)vec.back == 18);

    // Reverse the vector
    for (size_t i = 0; i != vec.size / 2; i++) {
        int32 *src = &((int32 *)vec.data)[i];
        int32 *dst = &((int32 *)vec.data)[vec.size - 1 - i];
        int32  tmp;

        tmp  = *dst;
        *dst = *src;
        *src = tmp;
    }
    // print_vector(&vec);
    // Output: { 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
    // 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16,
    // -17, }

    //! [Bubble sort]
    vec._cmp = &int32_cmp; // Set comparator function pointer
    vector_bsort(&vec);
    // print_vector(&vec);
    // Output:{ -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4,
    // -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    // 18 }
    //! [Bubble sort]

    //! [Custom binary search]
    int32 n = -2;
    idx     = _vector_bsearch(&vec, &n);
    assert(idx == 15);
    //! [Custom binary search]

    int32 key  = 4;
    void *addr = (int32 *)vector_bsearch(&vec, &key);
    printf("Key found at: %p\n", addr);

    /*int32 i32_a = 2;
    int32 i32_b = -2;

    printf("Decimal: %d \n", i32_a);
    printf("Hexadecimal: %08x \n", i32_a);
    printf("Octal: %011o \n", i32_a);
    printf("\n");
    printf("Decimal: %d \n", i32_b);
    printf("Hexadecimal: %08x \n", i32_b);
    printf("Octal: %011o \n", i32_b);

    for (size_t i = 0; i < sizeof(int32); i++) {
        int8 byte = *(int8 *)&i32_a;
        for (size_t j = 0; j < 8; j++) {
        }
    }*/

    vector_clear(&vec);
    assert(vec.data == NULL);
}
