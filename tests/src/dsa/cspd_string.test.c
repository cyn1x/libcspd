#include "cspd_dsa.test.h"
#include <cspd_assert.h>
#include <cspd_print.h>
#include <cspd_string.h>
#include <cspd_vector.h>
#include <string.h>

/******************************************************************************
 * Helper Declarations
 *****************************************************************************/

/* Creates a string with values from the given char array. */
#define ts_from(ARR) ts_from_impl((ARR), sizeof((ARR)[0]))

/* Verifies a string holds the expected characters in order. */
#define ts_expect(STR, ARR)                                                    \
    do {                                                                       \
        const cspd_string *_s = &(STR);                                        \
        const char        *_e = (ARR);                                         \
        const u8 *_b = cspd_string_is_inline(_s) ? _s->buffer : _s->data;      \
        for (usize i = 0; i < strlen(_e); ++i) {                               \
            cspd_assert(((char *)_b)[i] == _e[i]);                             \
        }                                                                      \
    } while (0)

static cspd_string ts_from_impl(const char *cstr, usize count);
static void        ts_expect_impl(const u8 *storage, const char *actual);

/******************************************************************************
 * Test Declarations
 *****************************************************************************/

static void test_init(void);
static void test_append(void);
static void test_concat(void);
static void test_join(void);

/******************************************************************************
 * Test Runner
 *****************************************************************************/

void cspd_string_test(void)
{
    test_init();
    test_append();
    test_concat();
    test_join();
}

/******************************************************************************
 * Test Definitions
 *****************************************************************************/

static void test_init(void)
{
    {
        cspd_string str;
        cspd_string_init(&str);

        u8 const *msb = &str.buffer[CSPD_STRING_META_BYTE];

        // String is inline but has a length of zero
        cspd_assert((*msb & 0x80) == (128u));
        cspd_assert((*msb & 0x80) == (1u << 7));
        cspd_assert((*msb & CSPD_STRING_META_BYTE) == (0));

        cspd_string_clear(&str);
    }

    {
        // Create a new inlined string with length equal to 11
        cspd_string str      = cspd_string_new("hello,world");
        char        actual[] = "hello,world";

        u8 const *msb        = &str.buffer[CSPD_STRING_META_BYTE];

        // Same value (11) declared three ways, for bit-notation reference
        cspd_assert((*msb & 0x7Fu) == 11u);
        cspd_assert((*msb & 0x7Fu) == ((1u << 3) | 3u));
        cspd_assert((*msb & 0x7Fu) == ((1u << 3) | (1u << 1) | (1u << 0)));

        // Check string has a NUL character, i.e. is a null-terminated string
        cspd_assert(str.buffer[12] == '\0');

        ts_expect(str, actual);

        // cspd_print_binary(&str.buffer[23], sizeof(u8));
        // Output: 10001011

        cspd_string_clear(&str);
    }

    {
        // Create a new inlined string with at maximum permitted length before a
        // memory allocation is required
        char cstr[CSPD_STRING_INLINE_LEN + 1];
        for (usize i = 0; i < CSPD_STRING_INLINE_LEN; ++i) {
            cstr[i] = 'x';
        }
        cspd_string str = cspd_string_new(cstr);

        u8 const *msb   = &str.buffer[CSPD_STRING_META_BYTE];

        cspd_assert((*msb & 0x7Fu) == 22u);
        cspd_assert(str.buffer[CSPD_STRING_INLINE_LEN] == '\0');
        cspd_assert(str.buffer[CSPD_STRING_INLINE_LEN - 1] == 'x');

        cspd_string_clear(&str);
    }

    {
        // Create a new string that will have its value allocated onto the heap.
        char cstr[CSPD_STRING_INLINE_SIZE];
        for (usize i = 0; i < CSPD_STRING_INLINE_SIZE - 1; ++i) {
            cstr[i] = 'x';
        }
        cspd_string str = cspd_string_new(cstr);

        cspd_assert(!cspd_string_is_inline(&str));
        cspd_assert(cspd_string_at(&str, 23) == '\0');
        cspd_assert(cspd_string_at(&str, 22) == 'x');
        cspd_assert(str.length == 23);

        cspd_string_clear(&str);
    }
}

static void test_append(void)
{
    {
        cspd_string str;
        cspd_string_init(&str);
        cspd_string_append(&str, "hello");

        // cspd_print_binary(&str.buffer[23], sizeof(u8));
        // Output: 10000101

        u8 const *msb = &str.buffer[CSPD_STRING_META_BYTE];

        cspd_assert(cspd_string_is_inline(&str));
        cspd_assert((*msb & 0x80) == (128u));
        cspd_assert((*msb & 0x7Fu) == 5u);

        cspd_assert(cspd_string_at(&str, 0) == 'h');
        cspd_assert(cspd_string_at(&str, 1) == 'e');
        cspd_assert(cspd_string_at(&str, 2) == 'l');
        cspd_assert(cspd_string_at(&str, 3) == 'l');
        cspd_assert(cspd_string_at(&str, 4) == 'o');
        cspd_assert(cspd_string_at(&str, 5) == '\0');

        cspd_string_append(&str, ",world");

        // cspd_print_binary(&str.buffer[23], sizeof(u8));
        // Output: 10001011

        cspd_assert(cspd_string_is_inline(&str));
        cspd_assert((*msb & 0x7Fu) == 11u);

        // NUL terminator should no longer be idx == 5
        cspd_assert(cspd_string_at(&str, 5) == ',');
        cspd_assert(cspd_string_at(&str, 6) == 'w');
        cspd_assert(cspd_string_at(&str, 7) == 'o');
        cspd_assert(cspd_string_at(&str, 8) == 'r');
        cspd_assert(cspd_string_at(&str, 9) == 'l');
        cspd_assert(cspd_string_at(&str, 10) == 'd');
        cspd_assert(cspd_string_at(&str, 11) == '\0');

        // cspd_print_fn("%s", str.buffer);
        // Output: hello,world

        cspd_string_clear(&str);
    }
}

static void test_concat(void)
{
    {
        //! [Concat string]
        cspd_string str      = cspd_string_new("the quick brown fox");
        cspd_string tmp      = cspd_string_new(" ");
        char        cstr[]   = "jumped over the lazy dog";
        char        actual[] = "the quick brown fox jumped over the lazy dog\0";

        u8 const   *msb      = &str.buffer[CSPD_STRING_META_BYTE];
        const char *parts[]  = {
            (char *)tmp.buffer,
            cstr,
        };

        cspd_assert(cspd_string_is_inline(&str));
        cspd_assert((*msb & 0x80) == (128u));
        cspd_assert((*msb & 0x7Fu) == 19u);

        cspd_string_concat(&str, parts, sizeof(parts) / sizeof(parts[0]));
        cspd_string_clear(&tmp);

        // cspd_print_fn("%s\n", str.data);
        // Output: the quick brown fox jumped over the lazy dog

        cspd_assert(!cspd_string_is_inline(&str));
        cspd_assert(str.capacity == 48);
        cspd_assert(str.length == 44);
        cspd_assert(str.data[45] == '\0');
        //! [Concat string]

        ts_expect(str, actual);

        cspd_string_clear(&str);
    }

    {
        cspd_string str;
        char        tmp_a[] = "lorem ";
        char        tmp_b[] = "ipsum ";
        char        tmp_c[] = "dolor ";
        char        tmp_d[] = "sit ";
        char        tmp_e[] = "amet";

        char actual[]       = "lorem ipsum dolor sit amet\0";

        const char *parts[] = {
            tmp_a, tmp_b, tmp_c, tmp_d, tmp_e,
        };

        cspd_string_init(&str);
        cspd_string_concat(&str, parts, sizeof(parts) / sizeof(parts[0]));

        cspd_assert(!cspd_string_is_inline(&str));
        cspd_assert(str.capacity == 32);
        cspd_assert(str.length == 26);
        cspd_assert(str.data[27] == '\0');

        ts_expect(str, actual);

        cspd_string_clear(&str);
    }
}

static void test_join(void)
{
    {
        //! [Join string]
        cspd_string str     = cspd_string_new("");
        cspd_string tmp_a   = cspd_string_new("hello");
        cspd_string tmp_b   = cspd_string_new("world");

        char sep            = ',';
        char actual[]       = "hello,world\0";

        u8 const   *msb     = &str.buffer[CSPD_STRING_META_BYTE];
        const char *parts[] = {
            (char *)tmp_a.buffer,
            (char *)tmp_b.buffer,
        };

        cspd_string_join(&str, sep, parts, sizeof(parts) / sizeof(parts[0]));

        cspd_string_clear(&tmp_a);
        cspd_string_clear(&tmp_b);

        // cspd_print_fn("%s", str.buffer);
        // Output: hello,world

        cspd_assert(cspd_string_is_inline(&str));
        cspd_assert((*msb & 0x80) == (128u));
        cspd_assert((*msb & 0x7Fu) == 11u);
        //! [Join string]

        ts_expect(str, actual);

        cspd_string_clear(&str);
    }

    {
        cspd_string str;
        char        tmp_a[] = "lorem";
        char        tmp_b[] = "ipsum";
        char        tmp_c[] = "dolor";
        char        tmp_d[] = "sit";
        char        tmp_e[] = "amet";

        char delim          = ' ';
        char actual[]       = "lorem ipsum dolor sit amet\0";

        const char *parts[] = {
            tmp_a, tmp_b, tmp_c, tmp_d, tmp_e,
        };

        cspd_string_init(&str);
        cspd_string_join(&str, delim, parts, sizeof(parts) / sizeof(parts[0]));

        cspd_assert(!cspd_string_is_inline(&str));
        cspd_assert(str.capacity == 32);
        cspd_assert(str.length == 26);
        cspd_assert(str.data[27] == '\0');

        ts_expect(str, actual);

        cspd_string_clear(&str);
    }
}

/******************************************************************************
 * Helper Definitions
 *****************************************************************************/

static cspd_string ts_from_impl(const char *cstr, usize count)
{
    cspd_string str;

    cspd_string_init(&str);
    cspd_string_concat(&str, &cstr, count);

    return str;
}
