/**
 * @file cmp.h
 */

#ifndef CMP_H
#define CMP_H

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef _WIN32
#ifdef LIBCSPD_EXPORTS
#define LIBCSPD_API __declspec(dllexport)
#else
#define LIBCSPD_API __declspec(dllimport)
#endif // LIBCSPD_EXPORTS
#elif __linux__
#define LIBCSPD_API __attribute__((visibility("default")))
#else
#define LIBCSPD_API
#endif // _WIN32

#define cmp(T)                                                                 \
    LIBCSPD_API int T##_cmp(const void *a, const void *b)                      \
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

inline cmp(int8) inline cmp(int16) inline cmp(int32) inline cmp(int64) inline cmp(
    uint8) inline cmp(uint16) inline cmp(uint32) inline cmp(uint64)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CMP_H
