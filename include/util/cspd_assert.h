/**
 * @file cspd_assert.h
 */

#if DEBUG
#define Assert(expression)                                                     \
    if (!(expression)) {                                                       \
        *(void *)0 = 0;                                                        \
    }
#else
#define Assert(expression)
#endif
