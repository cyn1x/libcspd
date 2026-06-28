/**
 * @file cspd_print.h
 * Generic `printf()` wrapper.
 *
 * @see http://www.robertgamble.net/2012/01/c11-generic-selections.html
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

/**
 * @brief Determines the format specifier of a data type.
 *
 * Dynamically infers the `printf()` format specifier.
 *
 * @param X The data type to be inferred.
 */
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

/**
 * @brief Prints a formatted string to the standard output.
 *
 * @param format A `printf()` format string.
 * @param ...    The variable arguments corresponding to the format string.
 */
static void cspd_print_fn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

/**
 * @brief Generic print function.
 *
 * Generic print function that takes the data to be printed `T` and a value `V`
 * to output after `T`, which could be a newline, blank space, or something
 * else.
 *
 * @param T The data to be printed.
 * @param V The value to output after the data has been printed.
 */

#define cspd_print(T, V) cspd_print_fn(cspd_print_any(T), T), cspd_print_fn(V);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_PRINT_H
