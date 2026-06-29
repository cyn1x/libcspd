/**
 * @file cspd_assert.h
 */

#if DEBUG

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
#define Assert(EXPRESSION)                                                     \
    if (!(EXPRESSION)) {                                                       \
        *(void *)0 = 0;                                                        \
    }

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
#define Assert(EXPRESSION)

#endif
