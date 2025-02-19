/**
 * @file print.h
 * Generic `printf()` wrapper.
 *
 * @see http://www.robertgamble.net/2012/01/c11-generic-selections.html
 */

/**
 * @def print_any(T)
 *
 * @brief Determines the format specifier of a data type.
 *
 * Dynamically infers the `printf()` format specifier.
 *
 * @param T The data type to be inferred.
 */

/**
 * @def print(T, S)
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

#ifndef PRINT_H
#define PRINT_H

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>

#ifdef __clang__
static void print_fn(const char *format, ...) __attribute__((unused));
#endif /* ifdef __clang__ */

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

static void print_fn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

#define print(T, S) print_fn(print_any(T), T), print_fn(S);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // PRINT_H
