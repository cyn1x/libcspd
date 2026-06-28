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

#ifdef __cplusplus
#define cspd_print(T, V) ; // TODO: C++ implementation

#else

/**
 * @brief Determines the format specifier of a data type.
 *
 * Dynamically infers the `printf()` format specifier.
 *
 * @param X The data type to be inferred.
 */
#define cspd_print_any(X)                                                      \
    _Generic((X),                                                              \
        i8: "%" PRIi8,                                                         \
        i16: "%" PRIi16,                                                       \
        i32: "%" PRIi32,                                                       \
        i64: "%" PRIi64,                                                       \
        u8: "%" PRIu8,                                                         \
        u16: "%" PRIu16,                                                       \
        u32: "%" PRIu32,                                                       \
        u64: "%" PRIu64,                                                       \
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
 * @param VALUE The data to be printed.
 * @param ARGS Additional values to be printed.
 */

#define cspd_print(VALUE, ARGS)                                                \
    cspd_print_fn(cspd_print_any(VALUE), VALUE), cspd_print_fn(ARGS);
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_PRINT_H
