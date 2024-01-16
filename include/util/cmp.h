/**
 * @file cmp.h
 * Dynamic comparator function implementation.
 * Supports dynamic initialization of data types for comparing values with that
 * data type.
 */

/**
 * @def cmp(T)
 *
 * @brief Comparator function initializer.
 *
 * Comparator function initializer that takes a data type to initialize the
 * comparator function for.
 *
 * @param T Data type to initialized for use with the comparator function.
 *
 * @b Example
 * @snippet defs.test.h Comparator type initialization
 * @b Example
 * @snippet vector.test.c Comparator function
 */

#ifndef CMP_H
#define CMP_H

#include "types.h"

#define cmp(T)                                                                 \
    /*                                                                         \
     * @brief Compares two variables for equality and inequality.              \
     *                                                                         \
     * Comparator function that compares two variables for equality.           \
     *                                                                         \
     * @param a Pointer to the first data type used to compare with.           \
     * @param b Pointer to the second data type used to compare against.       \
     *                                                                         \
     * @returns `-1` if `a < b`, `1` if `a > b`, or `0` if `a == b`.           \
     */                                                                        \
    int T##_cmp(const void *a, const void *b)                                  \
    {                                                                          \
        T arg1 = *(const T *)a;                                                \
        T arg2 = *(const T *)b;                                                \
                                                                               \
        if (arg1 < arg2) {                                                     \
            return -1;                                                         \
        }                                                                      \
        if (arg1 > arg2) {                                                     \
            return 1;                                                          \
        }                                                                      \
        return 0;                                                              \
    }

#endif // CMP_H
