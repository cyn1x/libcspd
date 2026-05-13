/**
 * @file cspd_print.h
 * Generic `printf()` wrapper.
 *
 * @see http://www.robertgamble.net/2012/01/c11-generic-selections.html
 */

/**
 * @def cspd_print_any(T)
 *
 * @brief Determines the format specifier of a data type.
 *
 * Dynamically infers the `printf()` format specifier.
 *
 * @param T The data type to be inferred.
 */

/**
 * @def cspd_print(T, S)
 *
 * @brief Generic print function.
 *
 * Generic print function that takes the data to be printed `T` and a string `S`
 * to output after `T`, which could be a newline, blank space, or something
 * else.
 *
 * @param T The data to be printed.
 * @param S The string to output after the data has been printed.
 */

#ifndef CSPD_PRINT_H
#define CSPD_PRINT_H

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>

#ifdef __clang__
static void cspd_print_fn(const char *format, ...) __attribute__((unused));
#endif /* ifdef __clang__ */

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __cplusplus
#define cspd_print(T, S) ; // TODO: C++ implementation

#else
#define cspd_print_any(X)                                                      \
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

static void cspd_print_fn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

#define cspd_print(T, S) cspd_print_fn(cspd_print_any(T), T), cspd_print_fn(S);
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_PRINT_H
