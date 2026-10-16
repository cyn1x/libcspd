/**
 * @file cspd_cmp.h
 * @brief Generic comparator function declaration.
 */

#ifndef CSPD_CMP_H
#define CSPD_CMP_H

/**
 * @brief Comparator function initializer.
 *
 * Comparator function initializer that takes a data type to initialize the
 * function with the `TYPE` parameter prefixed to the function name.
 *
 * @param TYPE Data type to initialized for use with the comparator function.
 *
 * @b Example
 * @snippet cspd_cmp.test.h Comparator type declaration
 */
#define cspd_cmp(TYPE)                                                         \
    /**                                                                        \
     * @brief Compares two variables for equality and inequality.              \
     *                                                                         \
     * Comparator function that compares two variables for equality.           \
     *                                                                         \
     * @param a Pointer to the first data type used to compare with.           \
     * @param b Pointer to the second data type used to compare against.       \
     *                                                                         \
     * @returns `-1` if `a < b`, `1` if `a > b`, or `0` if `a == b`.           \
     */                                                                        \
    static inline int TYPE##_cmp(const void *a, const void *b)                 \
    {                                                                          \
        TYPE arg1 = *(const TYPE *)a;                                          \
        TYPE arg2 = *(const TYPE *)b;                                          \
                                                                               \
        if (arg1 < arg2) {                                                     \
            return -1;                                                         \
        }                                                                      \
        if (arg1 > arg2) {                                                     \
            return 1;                                                          \
        }                                                                      \
        return 0;                                                              \
    }

#endif // CSPD_CMP_H
