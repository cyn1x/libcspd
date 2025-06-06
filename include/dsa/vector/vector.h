/**
 * @file vector.h
 */

/**
 * @def MIN_VECTOR_CAPACITY
 *
 * @brief The minimum capacity of the vector upon initialization.
 */

/**
 * @def print_vector(type, vec)
 *
 * @brief Prints the contents of the vector.
 *
 * Basic print function for C types residing in a vector by casting each element
 * to the specified type.
 *
 * @param type Type of data to be casted.
 * @param vec The vector to be printed out.
 */

/**
 * @typedef struct vector_t
 *
 * @brief Data structure for the vector.
 *
 * @var vector::data_size
 * The size of the data in bytes being stored in the vector.
 *
 * @var vector::capacity
 * The total capacity of the vector.
 *
 * @var vector::size
 * The total size of the vector.
 *
 * @var vector::data
 * Memory which has been allocated for the vector to store data.
 *
 * @var vector::front
 * Pointer to the first element in the vector.
 *
 * @var vector::back
 * Pointer to the last element in the vector.
 *
 * @var vector::_cmp
 * Comparator function used for sorting or searching. The library contains some
 * basic types as seen below, which can be assigned to the `_cmp` variable. You
 * can also provide your own comparator functions.
 *
 * @b Example
 * The provided comparator functions can be defined in a header file.
 * @include defs.test.h
 * Once defined, assign the address of the defined functions from the header
 * file to the comparator function pointer.
 * @snippet vector.test.c Comparator function
 */

/**
 * @fn void vector_init(vector_t *vec, size_t data_size)
 *
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
 * @snippet vector.test.c Initialize
 */

/**
 * @fn *vector_get(const vector_t *vec, size_t idx)
 *
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
 * @snippet vector.test.c Get element
 */

/**
 * @fn vector_set(vector_t *vec, size_t idx, const void *data)
 *
 * @brief Copies data to the vector.
 *
 * Copies data to the specified vector index and calls `vector_update()` to
 * cover the case of the `front` or `back` pointers being change.
 *
 * @param vec The vector to have data copied into.
 * @param idx The index to copy the data to.
 * @param data The data to be copied into the vector.
 */

/**
 * @fn vector_push(vector_t *vec, const void *data)
 *
 * @brief Appends an element to the vector.
 *
 * Adds an element to the end of the vector but will perform a `realloc`
 * beforehand if the vector is at maximum capacity.
 *
 * @param vec The vector to add an item to.
 * @param data The data to be appended in the vector.
 *
 * @b Example
 * @snippet vector.test.c Push elements
 */

/**
 * @fn vector_pop(vector_t *vec)
 *
 * @brief Removes the last element of the vector.
 *
 * Reduces the size of the vector by a single element and calls to update the
 * back pointer to the new last element after size reduction.
 *
 * @param vec The vector that requires the last element to be removed.
 */

/**
 * @fn vector_insert(vector_t *vec, size_t idx, size_t size, const void *data)
 *
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
 * @snippet vector.test.c Inserting data
 */

/**
 * @fn vector_erase(vector_t *vec, size_t begin, size_t end)
 *
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
 * @snippet vector.test.c Erasing data
 */

/**
 * @fn vector_clear(vector_t *vec)
 *
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

/**
 * @fn *vector_resize(vector_t *vec)
 *
 * @brief Resizes the vector.
 *
 * Increases the size of a vector by doubling the current capacity. This is a
 * helper function for other operations and should not be directly used.
 *
 * @param vec The vector to be resized.
 *
 * @returns The resized vector.
 */

/**
 * @fn *vector_copy(vector_t *dst, vector *src)
 *
 * @brief Copies data from one vector to the other.
 *
 * Copies data from vector `src` heap memory to vector `dst` heap memory.
 *
 * @param dst The destination for the datasource to be copied to.
 * @param src The datasource for the copy.
 */

/**
 * @fn *vector_reverse(vector_t *vec)
 *
 * @brief Reverses the order of elements in a vector
 *
 * Reverses the order of elements in the given vector.
 *
 * @param vec The vector to be reversed.
 */

/**
 * @fn vector_lsearch(vector_t *vec, const void *key)
 *
 * @brief Checks if an element exists in the vector.
 *
 * Sequentially checks all elements until a match is found or the entire length
 * of the vector has been traversed.
 *
 * @param vec The vector to be searched.
 * @param key The value to be searched for.
 *
 * @returns An index of `size_t` of the element that was found or SIZE_MAX if
 * not found.
 *
 * @b Example
 * @snippet vector.test.c Linear search
 *
 * @see https://en.wikipedia.org/wiki/Linear_search
 */

/**
 * @fn vector_bsearch(vector_t *vec, const void *key)
 *
 * @brief Checks if an element exists in the vector.
 *
 * Uses a divide-and-conquer approach in checking whether an element exists in
 * the vector. Use of this function requires the comparator function pointer to
 * be set.
 *
 * @warning The `_cmp` function pointer in the `vector` struct must be assigned
 * before calling this function.
 *
 * @warning This function assumes that the vector is sorted before being called.
 *
 * @param vec The vector to be searched.
 * @param data The value to be searched for.
 *
 * @returns An index of `size_t` of the element that was found or SIZE_MAX if
 * not found.
 *
 * @b Example
 * @snippet vector.test.c Custom binary search
 *
 * @see https://en.wikipedia.org/wiki/Binary_search
 */

/**
 * @fn vector_bsort(vector_t *vec)
 *
 * @brief Sorts a vector using the bubblesort algorithm.
 *
 * Sorts a vector using the bubble sort algorithm. It is not recommended to use
 * this algorithm over the others available. However, it remains in the library
 * for demonstration purposes. Use of this function requires the comparator
 * function pointer to be set.
 *
 * @warning The `_cmp` function pointer in the `vector` struct must be assigned
 * before calling this function.
 *
 * @param vec The vector to be sorted.
 *
 * @b Example
 * @snippet vector.test.c Bubble sort
 *
 * @see https://en.wikipedia.org/wiki/Bubble_sort
 */

/**
 * @fn vector_qsort(vector_t *vec ptrdiff_t lo, ptrdiff_t hi)
 *
 * @brief Sorts a vector using the quicksort algorithm.
 *
 * Sorts a vector using the quicksort algorithm. This quicksort algorithm makes
 * use of the Lomuto partition scheme.
 *
 * @param vec The vector to be sorted.
 * @param lo Index of the first element in the vector
 * @param hi Index of the last element of in the vector
 *
 * @see https://en.wikipedia.org/wiki/Quicksort
 */

/**
 * @fn vector_msort(vector_t *vec)
 *
 * @brief Sorts a vector using the mergesort algorithm.
 *
 * Sorts a vector using the top-down implementation of the mergesort algorithm.
 * Use of this function requires the comparator function to be set.
 *
 * @param vec The vector to be sorted.
 *
 * @see https://en.wikipedia.org/wiki/Merge_sort
 */

/**
 * @fn partition(vector_t *vec, ptrdiff_t lo, ptrdiff_t hi)
 *
 * @brief Divides the vector into two partitions.
 *
 * Divides the vector into two partitions and moves all elements to the left of
 * the pivot if they are less than or equal to the pivot.
 *
 * @param vec The vector to be partitioned.
 * @param lo Index of the first element in the vector
 * @param hi Index of the last element of in the vector
 *
 * @returns The index of the next pivot point.
 */

/**
 * @fn split_merge(vector_t *vec_b, size_t begin, size_t end, vector_t *vec_a)
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
 */

/**
 * @fn merge(vector_t *vec_b, size_t begin, size_t mid, size_t end, vector_t
 * *vec_a)
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
 */

/**
 * @fn update_pointers(vector_t *vec)
 *
 * @brief Updates the front and back pointers.
 *
 * Helper function that updates the front and back pointers if the calling
 * function deems them necessary to be updated.
 *
 * @param vec The vector to be updated.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "defs.h"
#include "types.h"
#include <stdbool.h>

#ifdef __clang__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MIN_CAPACITY 32

typedef struct vector
{
    size_t capacity;
    size_t size;
    size_t data_size;

    void  *data;
    void  *front;
    void  *back;

    int (*_cmp)(const void *, const void *);

} vector_t;

LIBCSPD_API void   vector_init(vector_t *vec, size_t data_size);
LIBCSPD_API void  *vector_get(const vector_t *vec, size_t idx);
LIBCSPD_API void   vector_set(vector_t *vec, size_t idx, const void *data);
LIBCSPD_API void   vector_push(vector_t *vec, const void *data);
LIBCSPD_API void   vector_pop(vector_t *vec);
LIBCSPD_API void   vector_insert(vector_t *vec, size_t idx, size_t size,
                                 const void *data);
LIBCSPD_API void   vector_erase(vector_t *vec, size_t begin, size_t end);
LIBCSPD_API void   vector_clear(vector_t *vec);
LIBCSPD_API void  *vector_resize(vector_t *vec, size_t size);
LIBCSPD_API void   vector_copy(vector_t *dst, vector_t *src);
LIBCSPD_API void   vector_reverse(vector_t *vec);
LIBCSPD_API size_t vector_lsearch(vector_t *vec, const void *key);
LIBCSPD_API size_t vector_bsearch(vector_t *vec, const void *key);
LIBCSPD_API void   vector_bsort(vector_t *vec);
LIBCSPD_API void   vector_qsort(vector_t *vec, ptrdiff_t lo, ptrdiff_t hi);
LIBCSPD_API void   vector_msort(vector_t *vec_a, size_t size, cmp_t cmp);

#define print_vector(type, vec)                                                \
    {                                                                          \
        printf("{ ");                                                          \
        for (size_t i = 0; i < (vec)->size; ++i) {                             \
            print((*(type *)vector_get(vec, i)), " ");                         \
        }                                                                      \
        printf("} \n");                                                        \
    }

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // VECTOR_H
