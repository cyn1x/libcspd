#define CSPD_EXPORTS

#include "cspd_vector.h"
#include "cspd_mem.h"
#include "cspd_util.h"

static const int MIN_CAPACITY = 32;

static ptrdiff_t partition(cspd_vector *vec, ptrdiff_t lo, ptrdiff_t hi);
static void      split_merge(cspd_vector *vec_b, size_t begin, size_t end,
                             cspd_vector *vec_a);
static void      merge(cspd_vector *vec_b, size_t begin, size_t mid, size_t end,
                       cspd_vector *vec_a);

void             cspd_vector_init(cspd_vector *vec, size_t data_size)
{
    vec->data_size = data_size;
    vec->capacity  = MIN_CAPACITY;
    vec->size      = 0;
    vec->data      = cspd_calloc(vec->capacity, vec->data_size);
}

void *cspd_vector_back(cspd_vector *vec)
{
    return cspd_vector_get(vec, vec->size - 1);
}

void *cspd_vector_front(cspd_vector *vec)
{
    return cspd_vector_get(vec, 0);
}

void *cspd_vector_get(const cspd_vector *vec, size_t idx)
{
    return (int8 *)vec->data + vec->data_size * idx;
}

void cspd_vector_set(cspd_vector *vec, size_t idx, const void *data)
{
    void *dst = (int8 *)vec->data + idx * vec->data_size;
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

void cspd_vector_pop(cspd_vector *vec)
{
    vec->size--;
}

void cspd_vector_insert(cspd_vector *vec, size_t idx, size_t size,
                        const void *data)
{
    // TODO: handle index out of bounds
    size_t amt = size / vec->data_size;

    vec->size += amt;
    if (vec->size >= vec->capacity) {
        vec = cspd_vector_resize(vec, 0);
    }
    void *src = cspd_vector_get(vec, idx);
    void *dst = cspd_vector_get(vec, idx + amt);

    // Use the previous vector_t size to determine the amount of bytes to be
    // moved before additional bytes are inserted
    ptrdiff_t diff   = idx - (vec->size - amt);
    size_t    mv_amt = llabs(diff);

    memmove(dst, src, mv_amt * vec->data_size);
    memcpy(src, data, amt * vec->data_size);
}

void cspd_vector_erase(cspd_vector *vec, size_t begin, size_t end)
{
    // TODO: check range is within bounds
    void  *dst = cspd_vector_get(vec, begin);
    void  *src = cspd_vector_get(vec, end);
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
}

void cspd_vector_clear(cspd_vector *vec)
{
    cspd_free(vec->data);
    vec->data_size = 0;
    vec->capacity  = 0;
    vec->size      = 0;
    vec->data      = NULL;
}

void *cspd_vector_resize(cspd_vector *vec, size_t size)
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
    for (size_t i = 0; i < vec->size / 2; i++) {
        void *src = cspd_vector_get(vec, i);
        void *dst = cspd_vector_get(vec, vec->size - 1 - i);

        cspd_swap(src, dst, vec->data_size);
    }
}

size_t cspd_vector_lsearch(cspd_vector *vec, const void *key)
{
    for (size_t idx = 0; idx < vec->size; idx++) {
        void *cmp    = cspd_vector_get(vec, idx);
        int   exists = memcmp(cmp, key, vec->data_size);

        if (exists == 0) {
            return idx;
        }
    }

    return SIZE_MAX;
}

size_t cspd_vector_bsearch(cspd_vector *vec, const void *key)
{
    size_t lo = 0;
    size_t hi = vec->size - 1;

    do {
        size_t m     = (lo + (hi - lo) / 2);
        void  *mid   = cspd_vector_get(vec, m);
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

void cspd_vector_bsort(cspd_vector *vec)
{
    for (size_t i = 0; i < vec->size; i++) {
        for (size_t j = 0; j < vec->size - 1 - i; j++) {
            void *a   = cspd_vector_get(vec, j);
            void *b   = cspd_vector_get(vec, j + 1);
            int   cmp = vec->_cmp(a, b);

            if (cmp != -1) {
                cspd_swap(a, b, vec->data_size);
            }
        }
    }
}

void cspd_vector_msort(cspd_vector *vec_a, size_t size, cspd_cmp cmp)
{
    cspd_vector vec_b;
    cspd_vector_init(&vec_b, sizeof(int32));
    vec_b._cmp = cmp;

    cspd_vector_copy(&vec_b, vec_a);
    split_merge(vec_a, 0, size, &vec_b);

    cspd_vector_clear(&vec_b);
}

void cspd_vector_qsort(cspd_vector *vec, ptrdiff_t lo, ptrdiff_t hi)
{
    if (lo >= hi) {
        return;
    }

    ptrdiff_t pvt_idx = partition(vec, lo, hi);

    cspd_vector_qsort(vec, lo, pvt_idx - 1);
    cspd_vector_qsort(vec, pvt_idx + 1, hi);
}

static ptrdiff_t partition(cspd_vector *vec, ptrdiff_t lo, ptrdiff_t hi)
{
    void     *pvt = cspd_vector_get(vec, hi);
    void     *tmp;
    ptrdiff_t idx = lo - 1;

    for (ptrdiff_t i = lo; i < hi; ++i) {
        void *curr = cspd_vector_get(vec, i);

        int   cmp  = vec->_cmp(curr, pvt);
        if (cmp != 1) {
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

static void split_merge(cspd_vector *vec_b, size_t begin, size_t end,
                        cspd_vector *vec_a)
{
    if (end - begin <= 1) {
        return;
    }

    size_t mid = (end + begin) / 2;

    split_merge(vec_a, begin, mid, vec_b);
    split_merge(vec_a, mid, end, vec_b);

    merge(vec_b, begin, mid, end, vec_a);
}

static void merge(cspd_vector *vec_b, size_t begin, size_t mid, size_t end,
                  cspd_vector *vec_a)
{
    size_t i = begin;
    size_t j = mid;

    for (size_t k = begin; k < end; k++) {
        void *lrh = cspd_vector_get(vec_a, i); // left run head
        void *rrh = cspd_vector_get(vec_a, j); // right run head
        int   cmp = vec_a->_cmp(lrh, rrh);

        void *tmp =
            cspd_vector_get(vec_b, k); // pointer to place sorted element
        if (i < mid && (j >= end || cmp != 1)) {
            cspd_swap(lrh, tmp, vec_b->data_size);
            i = i + 1;
        } else {
            cspd_swap(rrh, tmp, vec_b->data_size);
            j = j + 1;
        }
    }
}
