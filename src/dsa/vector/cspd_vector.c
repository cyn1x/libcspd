#define CSPD_EXPORTS

#include "cspd_vector.h"
#include "cspd_mem.h"
#include "cspd_util.h"
#include <string.h>

/**
 * @internal
 *
 * @brief Default minimum capacity of the vector.
 */
static const int MIN_CAPACITY = 32;

/**
 * @internal
 *
 * @brief Divides the vector into two partitions.
 *
 * Divides the vector into two partitions and moves all elements to the left of
 * the pivot if they are less than or equal to the pivot.
 *
 * @param vec The vector to be partitioned.
 * @param lo Index of the first element in the vector
 * @param hi Index of the last element of in the vector
 * @param cmp Comparator function pointer.
 *
 * @returns The index of the next pivot point.
 */
static isize partition(cspd_vector *vec, isize lo, isize hi, cspd_cmp cmp);

/**
 * @internal
 *
 * @brief Merges split runs from `vec_b` to `vec_a`.
 *
 * Splits `vec_a` into 2 runs, then sorts both runs into `vec_b`, then merges
 * both runs from `vec_b` to `vec_a`.
 *
 * @param vec_b The work vector
 * @param begin Index of the starter of the vector
 * @param end Index of the end of the vector
 * @param vec_a The vector to be sorted
 * @param cmp Comparator function pointer.
 *
 */
static void split_merge(cspd_vector *vec_b, usize begin, usize end,
                        cspd_vector *vec_a, cspd_cmp cmp);

/**
 * @internal
 *
 * @brief Helper function for mergesort that performs the sort.
 *
 * Helper function for `vector_msort()` that performs the sorting by use of the
 * vector comparator function.
 *
 * @param vec_b The work vector
 * @param begin Index of the starter of the vector
 * @param mid Index of the middle of the vector
 * @param end Index of the end of the vector
 * @param vec_a The vector to be sorted
 * @param cmp Comparator function pointer.
 */
static void merge(cspd_vector *vec_b, usize begin, usize mid, usize end,
                  cspd_vector *vec_a, cspd_cmp cmp);

void        cspd_vector_init(cspd_vector *vec, usize data_size)
{
    vec->data_size = data_size;
    vec->capacity  = MIN_CAPACITY;
    vec->size      = 0;
    vec->data      = cspd_calloc(vec->capacity, vec->data_size);
}

void cspd_vector_set(cspd_vector *vec, usize idx, const void *data)
{
    void *dst = (u8 *)vec->data + idx * vec->data_size;
    memcpy(dst, data, vec->data_size);
}

void cspd_vector_push(cspd_vector *vec, const void *data)
{
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = cspd_realloc(vec->data, vec->data_size * vec->capacity);
    }
    cspd_vector_set(vec, vec->size++, data);
}

void cspd_vector_insert(cspd_vector *vec, usize idx, usize size,
                        const void *data)
{
    // TODO: handle index out of bounds
    usize amt = size / vec->data_size;

    vec->size += amt;
    if (vec->size >= vec->capacity) {
        vec = cspd_vector_resize(vec, 0);
    }
    void *src = cspd_vector_get(vec, idx);
    void *dst = cspd_vector_get(vec, idx + amt);

    // Use the previous vector_t size to determine the amount of bytes to be
    // moved before additional bytes are inserted
    isize diff   = idx - (vec->size - amt);
    usize mv_amt = llabs(diff);

    memmove(dst, src, mv_amt * vec->data_size);
    memcpy(src, data, amt * vec->data_size);
}

void cspd_vector_erase(cspd_vector *vec, usize begin, usize end)
{
    // TODO: check range is within bounds
    void *dst = cspd_vector_get(vec, begin);
    void *src = cspd_vector_get(vec, end);
    usize amt = end - begin;

    // Invert the declarations above if erasing in a negative direction
    if (end < begin) {
        void *tmp = dst;
        dst       = src;
        src       = tmp;
        amt       = begin - end;
    }

    memmove(dst, src, (vec->size - amt) * vec->data_size);
    vec->size -= amt;
}

void cspd_vector_clear(cspd_vector *vec)
{
    cspd_free(vec->data);
    vec->data_size = 0;
    vec->capacity  = 0;
    vec->size      = 0;
    vec->data      = NULL;
}

void *cspd_vector_resize(cspd_vector *vec, usize size)
{
    if (size == 0) {
        vec->capacity *= 2;
    } else {
        vec->capacity = size;
    }

    // TODO: check if realloc was valid
    vec->data = cspd_realloc(vec->data, vec->data_size * vec->capacity);

    return vec;
}

void cspd_vector_copy(cspd_vector *dst, cspd_vector *src)
{
    // The destination vector_t is assumed to be empty
    cspd_vector_resize(dst, src->capacity);
    dst->size = src->size;
    memcpy(dst->data, src->data, src->size * src->data_size);
}

void cspd_vector_reverse(cspd_vector *vec)
{
    for (usize i = 0; i < vec->size / 2; i++) {
        void *src = cspd_vector_get(vec, i);
        void *dst = cspd_vector_get(vec, vec->size - 1 - i);

        cspd_swap(src, dst, vec->data_size);
    }
}

usize cspd_vector_lsearch(cspd_vector *vec, const void *key)
{
    for (usize idx = 0; idx < vec->size; idx++) {
        void *cmp    = cspd_vector_get(vec, idx);
        int   exists = memcmp(cmp, key, vec->data_size);

        if (exists == 0) {
            return idx;
        }
    }

    return SIZE_MAX;
}

usize cspd_vector_bsearch(cspd_vector *vec, const void *key, cspd_cmp cmp)
{
    usize lo = 0;
    usize hi = vec->size - 1;

    do {
        usize m     = (lo + (hi - lo) / 2);
        void *mid   = cspd_vector_get(vec, m);
        int   match = cmp(mid, key);

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

void cspd_vector_bsort(cspd_vector *vec, cspd_cmp cmp)
{
    for (usize i = 0; i < vec->size; i++) {
        for (usize j = 0; j < vec->size - 1 - i; j++) {
            void *a      = cspd_vector_get(vec, j);
            void *b      = cspd_vector_get(vec, j + 1);
            int   result = cmp(a, b);

            if (result != -1) {
                cspd_swap(a, b, vec->data_size);
            }
        }
    }
}

void cspd_vector_msort(cspd_vector *vec_a, usize size, cspd_cmp cmp)
{
    cspd_vector vec_b;
    cspd_vector_init(&vec_b, vec_a->data_size);

    cspd_vector_copy(&vec_b, vec_a);
    split_merge(vec_a, 0, size, &vec_b, cmp);

    cspd_vector_clear(&vec_b);
}

void cspd_vector_qsort(cspd_vector *vec, isize lo, isize hi, cspd_cmp cmp)
{
    if (lo >= hi) {
        return;
    }

    isize pvt_idx = partition(vec, lo, hi, cmp);

    cspd_vector_qsort(vec, lo, pvt_idx - 1, cmp);
    cspd_vector_qsort(vec, pvt_idx + 1, hi, cmp);
}

static isize partition(cspd_vector *vec, isize lo, isize hi, cspd_cmp cmp)
{
    void *pvt = cspd_vector_get(vec, hi);
    void *tmp;
    isize idx = lo - 1;

    for (isize i = lo; i < hi; ++i) {
        void *curr   = cspd_vector_get(vec, i);

        int   result = cmp(curr, pvt);
        if (result != 1) {
            idx++;
            tmp = cspd_vector_get(vec, idx);
            cspd_swap(curr, tmp, vec->data_size);
        }
    }

    idx++;
    tmp = cspd_vector_get(vec, idx);
    cspd_swap(tmp, pvt, vec->data_size);

    return idx;
}

static void split_merge(cspd_vector *vec_b, usize begin, usize end,
                        cspd_vector *vec_a, cspd_cmp cmp)
{
    if (end - begin <= 1) {
        return;
    }

    usize mid = (end + begin) / 2;

    split_merge(vec_a, begin, mid, vec_b, cmp);
    split_merge(vec_a, mid, end, vec_b, cmp);

    merge(vec_b, begin, mid, end, vec_a, cmp);
}

static void merge(cspd_vector *vec_b, usize begin, usize mid, usize end,
                  cspd_vector *vec_a, cspd_cmp cmp)
{
    usize i = begin;
    usize j = mid;

    for (usize k = begin; k < end; k++) {
        void *lrh    = cspd_vector_get(vec_a, i); // left run head
        void *rrh    = cspd_vector_get(vec_a, j); // right run head
        int   result = cmp(lrh, rrh);

        void *tmp =
            cspd_vector_get(vec_b, k); // pointer to place sorted element
        if (i < mid && (j >= end || result != 1)) {
            cspd_swap(lrh, tmp, vec_b->data_size);
            i = i + 1;
        } else {
            cspd_swap(rrh, tmp, vec_b->data_size);
            j = j + 1;
        }
    }
}
