#define LIBCSPD_EXPORTS

#include "vector.h"
#include "types.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

static ptrdiff_t partition(vector *vec, ptrdiff_t lo, ptrdiff_t hi);
static void split_merge(vector *vec_b, size_t begin, size_t end, vector *vec_a);
static void merge(vector *vec_b, size_t begin, size_t mid, size_t end,
                  vector *vec_a);
static void update_pointers(vector *vec);

void        vector_init(vector *vec, size_t data_size)
{
    vec->data_size = data_size;
    vec->capacity  = MIN_CAPACITY;
    vec->size      = 0;
    vec->data      = calloc(vec->capacity, vec->data_size);
    vec->front     = NULL;
    vec->back      = NULL;
}

void *vector_get(const vector *vec, size_t idx)
{
    return (int8 *)vec->data + vec->data_size * idx;
}

void vector_set(vector *vec, size_t idx, const void *data)
{
    void *dst = (int8 *)vec->data + idx * vec->data_size;
    memcpy(dst, data, vec->data_size);

    update_pointers(vec);
}

void vector_push(vector *vec, const void *data)
{
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->data_size * vec->capacity);
    }
    vector_set(vec, vec->size++, data);
}

void vector_pop(vector *vec)
{
    vec->size--;
    vec->back = vector_get(vec, vec->size - 1);
}

void vector_insert(vector *vec, size_t idx, size_t size, const void *data)
{
    // TODO: handle index out of bounds
    size_t amt = size / vec->data_size;

    vec->size += amt;
    if (vec->size >= vec->capacity) {
        vec = vector_resize(vec, 0);
    }
    void *src = vector_get(vec, idx);
    void *dst = vector_get(vec, idx + amt);

    // Use the previous vector size to determine the amount of bytes to be moved
    // before additional bytes are inserted
    ptrdiff_t diff   = idx - (vec->size - amt);
    size_t    mv_amt = llabs(diff);

    memmove(dst, src, mv_amt * vec->data_size);
    memcpy(src, data, amt * vec->data_size);

    update_pointers(vec);
}

void vector_erase(vector *vec, size_t begin, size_t end)
{
    // TODO: check range is within bounds
    void  *dst = vector_get(vec, begin);
    void  *src = vector_get(vec, end);
    size_t amt = end - begin;

    // Invert the declarations above if erasing in a negative direction
    if (end < begin) {
        void *tmp = dst;
        dst       = src;
        src       = tmp;
        amt       = begin - end;
    }

    memmove(dst, src, (vec->size - amt) * vec->data_size);

    vec->size -= amt;
    if (vec->size == 0) {
        vec->front = vec->back = NULL;
        return;
    }

    update_pointers(vec);
}

void vector_clear(vector *vec)
{
    free(vec->data);
    vec->data_size = 0;
    vec->capacity  = 0;
    vec->size      = 0;
    vec->data      = NULL;
    vec->front     = NULL;
    vec->back      = NULL;
}

void *vector_resize(vector *vec, size_t size)
{
    if (size == 0) {
        vec->capacity *= 2;
    } else {
        vec->capacity = size;
    }

    // TODO: check if realloc was valid
    vec->data = realloc(vec->data, vec->data_size * vec->capacity);

    return vec;
}

void vector_copy(vector *dst, vector *src)
{
    // The destination vector is assumed to be empty
    vector_resize(dst, src->capacity);
    dst->size = src->size;
    memcpy(dst->data, src->data, src->size * src->data_size);
}

void vector_reverse(vector *vec)
{
    for (size_t i = 0; i < vec->size / 2; i++) {
        void *src = vector_get(vec, i);
        void *dst = vector_get(vec, vec->size - 1 - i);

        swap(src, dst, vec->data_size);
    }
}

size_t vector_lsearch(vector *vec, const void *key)
{
    for (size_t idx = 0; idx < vec->size; idx++) {
        void *cmp    = vector_get(vec, idx);
        int   exists = memcmp(cmp, key, vec->data_size);

        if (exists == 0) {
            return idx;
        }
    }

    return SIZE_MAX;
}

void *vector_bsearch(vector *vec, const void *key)
{
    void *res = bsearch(key, vec->data, vec->size, vec->data_size, vec->_cmp);

    return res;
}

size_t vector_binary_search(vector *vec, const void *key)
{
    size_t lo = 0;
    size_t hi = vec->size - 1;

    do {
        size_t m     = (lo + (hi - lo) / 2);
        void  *mid   = vector_get(vec, m);
        int    match = vec->_cmp(mid, key);

        if (match == 0) {
            return m;
        } else if (match > 0) {
            hi = m;
        } else {
            lo = m + 1;
        }
    } while (lo < hi);

    return SIZE_MAX;
}

void vector_bsort(vector *vec)
{
    for (size_t i = 0; i < vec->size; i++) {
        for (size_t j = 0; j < vec->size - 1 - i; j++) {
            void *a   = vector_get(vec, j);
            void *b   = vector_get(vec, j + 1);
            int   cmp = vec->_cmp(a, b);

            if (cmp != -1) {
                swap(a, b, vec->data_size);
            }
        }
    }
}

void vector_qsort(vector *vec)
{
    qsort(vec, vec->size, vec->data_size, vec->_cmp);
}

void vector_msort(vector *vec_a, vector *vec_b, size_t size)
{
    vector_copy(vec_b, vec_a);
    split_merge(vec_a, 0, size, vec_b);
}

void vector_quicksort(vector *vec, ptrdiff_t lo, ptrdiff_t hi)
{
    if (lo >= hi) {
        return;
    }

    ptrdiff_t pvt_idx = partition(vec, lo, hi);

    vector_quicksort(vec, lo, pvt_idx - 1);
    vector_quicksort(vec, pvt_idx + 1, hi);
}

static ptrdiff_t partition(vector *vec, ptrdiff_t lo, ptrdiff_t hi)
{
    void     *pvt = vector_get(vec, hi);
    void     *tmp;
    ptrdiff_t idx = lo - 1;

    for (ptrdiff_t i = lo; i < hi; ++i) {
        void *curr = vector_get(vec, i);

        int   cmp  = vec->_cmp(curr, pvt);
        if (cmp != 1) {
            idx++;
            tmp = vector_get(vec, idx);
            swap(curr, tmp, vec->data_size);
        }
    }

    idx++;
    tmp = vector_get(vec, idx);
    swap(tmp, pvt, vec->data_size);

    return idx;
}

static void split_merge(vector *vec_b, size_t begin, size_t end, vector *vec_a)
{
    if (end - begin <= 1) {
        return;
    }

    size_t mid = (end + begin) / 2;

    split_merge(vec_a, begin, mid, vec_b);
    split_merge(vec_a, mid, end, vec_b);

    merge(vec_b, begin, mid, end, vec_a);
}

static void merge(vector *vec_b, size_t begin, size_t mid, size_t end,
                  vector *vec_a)
{
    size_t i = begin;
    size_t j = mid;

    for (size_t k = begin; k < end; k++) {
        void *lrh = vector_get(vec_a, i); // left run head
        void *rrh = vector_get(vec_a, j); // right run head
        int   cmp = vec_a->_cmp(lrh, rrh);

        void *tmp = vector_get(vec_b, k); // pointer to place sorted element
        if (i < mid && (j >= end || cmp != 1)) {
            swap(lrh, tmp, vec_b->data_size);
            i = i + 1;
        } else {
            swap(rrh, tmp, vec_b->data_size);
            j = j + 1;
        }
    }
}

static void update_pointers(vector *vec)
{
    void *front = vector_get(vec, 0);
    void *back  = vector_get(vec, vec->size - 1);
    if (vec->size == 1) {
        vec->front = vec->back = front;
        return;
    }

    if (vec->front != front) {
        vec->front = front;
    }
    if (vec->back != back) {
        vec->back = back;
    }
}
