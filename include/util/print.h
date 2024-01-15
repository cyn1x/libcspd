/**
 * @file print.h
 */

#ifndef PRINT_H
#define PRINT_H

#include "types.h"
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define print_any(X)                                                           \
    _Generic((X),                                                              \
        int8: "%" PRIi8,                                                       \
        int16: "%" PRIi16,                                                     \
        int32: "%" PRIi32,                                                     \
        int64: "%" PRIi64,                                                     \
        uint8: "%" PRIu8,                                                      \
        uint16: "%" PRIu16,                                                    \
        uint32: "%" PRIu32,                                                    \
        uint64: "%" PRIu64,                                                    \
        void *: "%p")

#define print(T, S) printf(print_any(T), T), printf(S);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // PRINT_H
