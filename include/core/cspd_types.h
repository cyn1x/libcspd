/**
 * @file cspd_types.h
 *
 * @brief Custom type definitions.
 *
 * Type definition aliases for C data types, and custom type definitions for
 * commonly used type signatures in the library.
 *
 * @see https://en.wikipedia.org/wiki/C_data_types
 */

#ifndef CSPD_TYPES_H
#define CSPD_TYPES_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Callback function type `cspd_cmp`.
 *
 * Simplified function pointer signature which can be declared with any type.
 *
 * @note This can be bypassed by defining a different comparator function. As
 * long as the function signature is `int (*)(const void *, const void *)`, it
 * can be passed as an argument to any function with a parameter that has the
 * same signature.
 *
 * @par Example
 * @code
 * #include <assert.h>
 * #include <cspd_cmp.h>
 * #include <cspd_types.h>
 * #include <stdlib.h>
 *
 * // Declare comparator function of type `i32`
 * cspd_cmp(i32);
 *
 * int main(int argc, char *argv[])
 * {
 *     // Create an unsorted array and sort it using the built-in quicksort.
 *     i32 arr[] = {7, 8, 7, 4, 10, 3, 5};
 *     qsort(&arr, 7, sizeof(i32), i32_cmp);
 *
 *     // Assert that the array is sorted
 *     i32 const *expected = (i32[]){3, 4, 5, 7, 7, 8, 10};
 *     for (size_t i = 0; i < 7; ++i) {
 *         assert(arr[i] == expected[i]);
 *     }
 *
 *     return 0;
 * }
 * @endcode
 *
 * @b Example
 * @snippet cspd_cmp.test.h Comparator type declaration
 */
typedef int (*cspd_cmp)(const void *, const void *);

/**
 * @brief Alias for type `int8_t`.
 */
typedef int8_t i8;

/**
 * @brief Alias for type `int16_t`.
 */
typedef int16_t i16;

/**
 * @brief Alias for type `int32_t`.
 */
typedef int32_t i32;

/**
 * @brief Alias for type `int64_t`.
 */
typedef int64_t i64;

/**
 * @brief Alias for type `uint8_t`.
 */
typedef uint8_t u8;

/**
 * @brief Alias for type `uint16_t`.
 */
typedef uint16_t u16;

/**
 * @brief Alias for type `uint32_t`.
 */
typedef uint32_t u32;

/**
 * @brief Alias for type `uint64_t`.
 */
typedef uint64_t u64;

/**
 * @brief Alias for type `float_t`.
 */
typedef float_t f32;

/**
 * @brief Alias for type `double_t`.
 */
typedef double_t f64;

/**
 * @brief Alias for type `size_t`.
 */
typedef size_t usize;

/**
 * @brief Alias for type `ptrdiff_t`.
 */
typedef ptrdiff_t isize;

#endif // CSPD_TYPES_H
