/**
 * @file cspd_assert.h
 * @brief Assertion functions for evaluating conditions.
 */

#ifndef CSPD_ASSERT_H
#define CSPD_ASSERT_H

#if DEBUG

#include "cspd_print.h"

/**
 * @internal
 *
 * @brief Evaluates an expression.
 *
 * Generates a stub assertion function for release builds.
 *
 * @warning The program will panic in debug mode if the expression evaluates to
 * false.
 *
 * @param EXPRESSION  The expression to be evaluated.
 */

#define cspd_assert(EXPRESSION)                                                \
    do {                                                                       \
        if (!(EXPRESSION)) {                                                   \
            fprintf(stderr,                                                    \
                    "Assertion failed: `%s`, file %s, line %d, function %s ",  \
                    #EXPRESSION, __FILE__, __LINE__, __func__);                \
            abort();                                                           \
        }                                                                      \
    } while (0)

#else

/**
 * @internal
 *
 * @brief Stub assertion function.
 *
 * Generates a stub assertion function for release builds that should be
 * detected as a no-op by the compiler.
 *
 * @param EXPRESSION  The expression to be evaluated.
 *
 * @see https://en.wikipedia.org/wiki/NOP_(code)#C_and_derivatives
 */
#define cspd_assert(EXPRESSION) ((void)0)

#endif // DEBUG

#endif // CSPD_ASSERT_H
