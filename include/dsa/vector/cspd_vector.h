/**
 * @file cspd_vector.h
 */

#ifndef CSPD_VECTOR_H
#define CSPD_VECTOR_H

#include "cspd_defs.h"
#include "cspd_types.h"

#ifdef __clang__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Data structure for the vector.
 *
 * @var cspd_vector::capacity
 * The total capacity of the vector.
 *
 * @var cspd_vector::size
 * The total size of the vector.
 *
 * @var cspd_vector::data_size
 * The size of the data in bytes being stored in the vector.
 *
 * @var cspd_vector::data
 * Memory which has been allocated for the vector to store data.
 */
typedef struct cspd_vector_t
{
    usize capacity;
    usize size;
    usize data_size;
    void *data;

} cspd_vector;

/**
 * @brief Initializes a new vector.
 *
 * Sets a minimum capacity to prevent expensive memory reallocations soon after
 * initializing. Memory is allocated by calling `calloc` to zero
 * the allocated memory as not all of it will likely be initialized by the user
 * after initialization.
 *
 * @param vec The vector to be initialized.
 * @param data_size The size of the data type in bytes.
 *
 * @b Example
 * @snippet cspd_vector.test.c Initialize
 */
CSPD_API void cspd_vector_init(cspd_vector *vec, usize data_size);

/**
 * @brief Copies data to the vector.
 *
 * Copies data to the specified vector index and calls `vector_update()` to
 * cover the case of the `front` or `back` pointers being change.
 *
 * @param vec The vector to have data copied into.
 * @param idx The index to copy the data to.
 * @param data The data to be copied into the vector.
 */
CSPD_API void cspd_vector_set(cspd_vector *vec, usize idx, const void *data);

/**
 * @brief Appends an element to the vector.
 *
 * Adds an element to the end of the vector but will perform a `realloc`
 * beforehand if the vector is at maximum capacity.
 *
 * @param vec The vector to add an item to.
 * @param data The data to be appended in the vector.
 *
 * @b Example
 * @snippet cspd_vector.test.c Push elements
 */
CSPD_API void cspd_vector_push(cspd_vector *vec, const void *data);

/**
 * @brief Inserts one or many elements at the specified index.
 *
 * Inserts data at the specified index after calculating the amount of data to
 * be moved ahead, if any, in preparation for the resulting memory copy.
 *
 * @param vec The vector to insert the data.
 * @param idx The vector index where to insert data.
 * @param size The size of the data being inserted in bytes.
 * @param data The data being inserted.
 *
 * @b Example
 * @snippet cspd_vector.test.c Inserting data
 */
CSPD_API void cspd_vector_insert(cspd_vector *vec, usize idx, usize size,
                                 const void *data);

/**
 * @brief Erases one or many elements from a vector.
 *
 * Erases data that has a size in bytes in either direction from the given
 * index. The memory will be compacted after the erasure with the vector size
 * updated in addition.
 *
 * @param vec The vector to erase data from.
 * @param begin The starting position of the erasure.
 * @param end The end position of the erasure.
 *
 * @b Example
 * @snippet cspd_vector.test.c Erasing data
 */
CSPD_API void cspd_vector_erase(cspd_vector *vec, usize begin, usize end);

/**
 * @brief Removes all items from a vector.
 *
 * Removes all items from a vector by freeing the memory consumed. The vector
 * should no longer be used after this operation unless reinitialized.
 *
 * @warning This function should be called after the vector is no longer
 * required to prevent memory leaks.
 *
 * @param vec The vector to be deleted.
 */
CSPD_API void cspd_vector_clear(cspd_vector *vec);

/**
 * @brief Resizes the vector.
 *
 * Increases the size of a vector by doubling the current capacity. This is a
 * helper function for other operations and should not be directly used.
 *
 * @param vec The vector to be resized.
 *
 * @returns The resized vector.
 */
CSPD_API void *cspd_vector_resize(cspd_vector *vec, usize size);

/**
 * @brief Copies data from one vector to the other.
 *
 * Copies data from vector `src` heap memory to vector `dst` heap memory.
 *
 * @param dst The destination for the datasource to be copied to.
 * @param src The datasource for the copy.
 */
CSPD_API void cspd_vector_copy(cspd_vector *dst, cspd_vector *src);

/**
 * @brief Reverses the order of elements in a vector
 *
 * Reverses the order of elements in the given vector.
 *
 * @param vec The vector to be reversed.
 */
CSPD_API void cspd_vector_reverse(cspd_vector *vec);

/**
 * @brief Checks if an element exists in the vector.
 *
 * Sequentially checks all elements until a match is found or the entire length
 * of the vector has been traversed.
 *
 * @param vec The vector to be searched.
 * @param key The value to be searched for.
 *
 * @returns An index of `usize` of the element that was found or SIZE_MAX if
 * not found.
 *
 * @b Example
 * @snippet cspd_vector.test.c Linear search
 *
 * @see https://en.wikipedia.org/wiki/Linear_search
 */
CSPD_API usize cspd_vector_lsearch(cspd_vector *vec, const void *key);

/**
 * @brief Checks if an element exists in the vector.
 *
 * Uses a divide-and-conquer approach in checking whether an element exists in
 * the vector.
 *
 * @param vec The vector to be searched.
 * @param data The value to be searched for.
 * @param cmp Comparator function.
 *
 * @returns An index of `usize` of the element that was found or SIZE_MAX if
 * not found.
 *
 * @b Example
 * @snippet cspd_vector.test.c Custom binary search
 *
 * @see https://en.wikipedia.org/wiki/Binary_search
 */
CSPD_API usize cspd_vector_bsearch(cspd_vector *vec, const void *key,
                                   cspd_cmp cmp);

/**
 * @brief Sorts a vector using the bubblesort algorithm.
 *
 * Sorts a vector using the bubble sort algorithm. It is not recommended to use
 * this algorithm over the others available. However, it remains in the library
 * for demonstration purposes.
 *
 * @param vec The vector to be sorted.
 * @param cmp Comparator function.
 *
 * @b Example
 * @snippet cspd_vector.test.c Bubble sort
 *
 * @see https://en.wikipedia.org/wiki/Bubble_sort
 */

CSPD_API void cspd_vector_bsort(cspd_vector *vec, cspd_cmp cmp);

/**
 * @brief Sorts a vector using the quicksort algorithm.
 *
 * Sorts a vector using the quicksort algorithm. This quicksort algorithm makes
 * use of the Lomuto partition scheme.
 *
 * @param vec The vector to be sorted.
 * @param lo Index of the first element in the vector
 * @param hi Index of the last element of in the vector
 * @param cmp Comparator function.
 *
 * @returns The index of the next pivot point.
 *
 * @see https://en.wikipedia.org/wiki/Quicksort
 */
CSPD_API void cspd_vector_qsort(cspd_vector *vec, isize lo, isize hi,
                                cspd_cmp cmp);

/**
 * @brief Sorts a vector using the mergesort algorithm.
 *
 * Sorts a vector using the top-down implementation of the mergesort algorithm.
 *
 * @param vec The vector to be sorted.
 * @param cmp Comparator function.
 *
 * @see https://en.wikipedia.org/wiki/Merge_sort
 */
CSPD_API void cspd_vector_msort(cspd_vector *vec_a, usize size, cspd_cmp cmp);

/**
 * @brief Retrieves an element from the vector.
 *
 * Retrieves an element from the vector at the specified index.
 *
 * @param vec The vector to retrieve an element from.
 * @param idx The index of the elment to retrieve.
 *
 * @returns A void pointer to the element.
 *
 * @b Example
 * @snippet cspd_vector.test.c Get element
 */
static inline void *cspd_vector_get(const cspd_vector *vec, usize idx)
{
    return (u8 *)vec->data + vec->data_size * idx;
}

/**
 * @brief Retrieves the last element in the vector.
 *
 * @param vec The vector to retrieve the element from.
 *
 * @returns Pointer to the last element in the vector.
 */
static inline void *cspd_vector_back(const cspd_vector *vec)
{
    return cspd_vector_get(vec, vec->size - 1);
}

/**
 * @brief Retrieves the first element in the vector.
 *
 * @param vec The vector to retrieve the element from.
 *
 * @returns Pointer to the first element in the vector.
 */
static inline void *cspd_vector_front(const cspd_vector *vec)
{
    return cspd_vector_get(vec, 0);
}

/**
 * @brief Removes the last element of the vector.
 *
 * Reduces the size of the vector by a single element and calls to update the
 * back pointer to the new last element after size reduction.
 *
 * @param vec The vector that requires the last element to be removed.
 */
static inline void cspd_vector_pop(cspd_vector *vec)
{
    vec->size--;
}

/**
 * @brief Prints the contents of the vector.
 *
 * Basic print function for C types residing in a vector by casting each element
 * to the specified type.
 *
 * @param TYPE Type of data to be casted.
 * @param VEC The vector to be printed out.
 */
#define cspd_print_vector(TYPE, VEC)                                           \
    {                                                                          \
        printf("{ ");                                                          \
        for (usize i = 0; i < (VEC)->size; ++i) {                              \
            cspd_print((*(TYPE *)cspd_vector_get(VEC, i)), " ");               \
        }                                                                      \
        printf("} \n");                                                        \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_VECTOR_H
