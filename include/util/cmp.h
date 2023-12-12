/**
 * @file cmp.h
 */

#ifndef CMP_H
#define CMP_H

#include "types.h"

#define cmp(T)                                                                 \
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
