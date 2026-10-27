#define CSPD_EXPORTS

#include "cspd_vector.h"
#include "cspd_assert.h"
#include "cspd_bytes.h"
#include "cspd_mem.h"

/**
 * @brief Minimum capacity of the vector.
 *
 * Any allocation smaller than this value is raised to this value.
 */
#define MIN_SIZE 32

/**
 * @brief Capacity granularity in bytes.
 *
 * Allocation sizes are rounded up to a multiple of this value.
 *
 * @note Must be a power of two, as the rounding uses a bitmask.
 */
#define QUANT    32

// Enforce the power-of-two requirement documented on QUANT.
_Static_assert((QUANT & (QUANT - 1)) == 0, "QUANT must be a power of two");

/**
 * @internal
 *
 * @brief Copies data to the vector.
 *
 * Calculates the index position by multiplying the given `idx` by
 * `vec->data_size`, and copies the `data` to that index.
 *
 * @param vec The vector to have data copied into.
 * @param idx The index to copy the data to.
 * @param data The data to be copied into the vector.
 */
static void set(cspd_vector *vec, usize idx, const void *data);

/**
 * @internal
 *
 * @brief Resizes the vector.
 *
 * Increases the size of a vector by doubling the current capacity. This is a
 * helper function for other operations and should not be directly used.
 *
 * @note If the vector has just been initialized (i.e. `vec->size` and
 * `vec->capacity` are zero), the given `size` parameter will be the initial
 * starting size.
 *
 * @param vec The vector to be resized.
 * @param size The minimum required capacity.
 */
static void resize(cspd_vector *vec, usize size);

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

void cspd_vector_init(cspd_vector *vec, usize data_size)
{
    cspd_assert(vec != NULL);

    vec->data_size = data_size;
    vec->capacity  = 0;
    vec->size      = 0;
    vec->data      = NULL;

    usize len      = MIN_SIZE;
    usize size     = len * vec->data_size;
    vec->data      = cspd_calloc(size, vec->data_size);

    if (vec->data) {
        vec->capacity = len;
    }
}

void cspd_vector_push(cspd_vector *vec, const void *data)
{
    if (vec->size == vec->capacity) {
        resize(vec, vec->size + 1);
    }
    set(vec, vec->size++, data);
}

void cspd_vector_addrange(cspd_vector *vec, usize size, const void *data)
{
    usize amt = size / vec->data_size;

    vec->size += amt;
    if (vec->size >= vec->capacity) {
        resize(vec, vec->capacity + amt);
    }
    void *src = cspd_vector_get(vec, vec->size - amt);

    memcpy(src, data, amt * vec->data_size);
}

void cspd_vector_insert(cspd_vector *vec, usize idx, usize size,
                        const void *data)
{
    // TODO: handle index out of bounds
    usize amt = size / vec->data_size;

    vec->size += amt;
    if (vec->size >= vec->capacity) {
        resize(vec, vec->size);
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
    // TODO: #0034 - Check range is within bounds
    usize lo   = begin < end ? begin : end;
    usize hi   = begin < end ? end : begin;
    usize amt  = hi - lo + 1;
    usize tail = vec->size - (hi + 1); // elements after the erased range

    memmove(cspd_vector_get(vec, lo), cspd_vector_get(vec, hi + 1),
            tail * vec->data_size);
    vec->size -= amt;
}

void cspd_vector_clear(cspd_vector *vec)
{
    cspd_assert(vec != NULL);

    cspd_free(vec->data);
    vec->data_size = 0;
    vec->capacity  = 0;
    vec->size      = 0;
    vec->data      = NULL;
}

void cspd_vector_copy(cspd_vector *dst, cspd_vector *src)
{
    // The destination vector_t is assumed to be empty
    resize(dst, src->capacity);
    dst->size = src->size;
    memcpy(dst->data, src->data, src->size * src->data_size);
}

void cspd_vector_reverse(cspd_vector *vec)
{
    for (usize i = 0; i < vec->size / 2; i++) {
        void *src = cspd_vector_get(vec, i);
        void *dst = cspd_vector_get(vec, vec->size - 1 - i);

        cspd_memswap(src, dst, vec->data_size);
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
        }
        else if (match > 0) {
            hi = m;
        }
        else {
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
                cspd_memswap(a, b, vec->data_size);
            }
        }
    }
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

void cspd_vector_msort(cspd_vector *vec_a, usize size, cspd_cmp cmp)
{
    cspd_vector vec_b;
    cspd_vector_init(&vec_b, vec_a->data_size);

    cspd_vector_copy(&vec_b, vec_a);
    split_merge(vec_a, 0, size, &vec_b, cmp);

    cspd_vector_clear(&vec_b);
}

static void set(cspd_vector *vec, usize idx, const void *data)
{
    void *dst = (u8 *)vec->data + idx * vec->data_size;
    memcpy(dst, data, vec->data_size);
}

static void resize(cspd_vector *vec, usize size)
{
    if (vec->capacity == 0) {
        cspd_vector_init(vec, vec->data_size);
        return;
    }

    while (vec->capacity < size) {
        vec->capacity *= 2;
    }

    vec->data = cspd_realloc(vec->data, vec->data_size * vec->capacity);
}

static isize partition(cspd_vector *vec, isize lo, isize hi, cspd_cmp cmp)
{
    void *pvt = cspd_vector_get(vec, hi);
    void *tmp;
    isize idx = lo - 1;

    for (isize i = lo; i < hi; ++i) {
        void *curr = cspd_vector_get(vec, i);

        int result = cmp(curr, pvt);
        if (result != 1) {
            idx++;
            tmp = cspd_vector_get(vec, idx);
            cspd_memswap(curr, tmp, vec->data_size);
        }
    }

    idx++;
    tmp = cspd_vector_get(vec, idx);
    cspd_memswap(tmp, pvt, vec->data_size);

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
            cspd_memswap(lrh, tmp, vec_b->data_size);
            i = i + 1;
        }
        else {
            cspd_memswap(rrh, tmp, vec_b->data_size);
            j = j + 1;
        }
    }
}
