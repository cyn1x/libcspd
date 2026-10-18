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
#define ts_from(ARR)                                                           \
    ts_from_impl((ARR), sizeof(ARR) / sizeof((ARR)[0]), sizeof((ARR)[0]))

static cspd_string ts_from_impl(const char *cstr, usize count);
static void        ts_expect_impl(cspd_string *str, const char *actual);

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
    cspd_string str_a;
    cspd_string str_b;
    cspd_string str_c = cspd_string_new("hello,world");

    cspd_string_init(&str_a);
    cspd_string_init(&str_b);

    cspd_assert(str_a.capacity == 16 && str_a.length == 0 &&
                str_a.data != NULL);
    cspd_assert(str_b.capacity >= 16 && str_b.length == 0 &&
                str_b.data != NULL);
    cspd_assert(str_c.capacity >= 12 && str_c.length == 11 &&
                str_c.data != NULL);

    cspd_string_clear(&str_a);
    cspd_string_clear(&str_b);
    cspd_string_clear(&str_c);
}

static void test_append(void)
{
    {
        //! [Append string]
        cspd_string str;

        cspd_string_init(&str);
        cspd_string_append(&str, "libcspd");

        cspd_assert(cspd_string_at(&str, 0) == 'l');
        cspd_assert(cspd_string_at(&str, 1) == 'i');
        cspd_assert(cspd_string_at(&str, 2) == 'b');
        cspd_assert(cspd_string_at(&str, 3) == 'c');
        cspd_assert(cspd_string_at(&str, 4) == 's');
        cspd_assert(cspd_string_at(&str, 5) == 'p');
        cspd_assert(cspd_string_at(&str, 6) == 'd');
        cspd_assert(cspd_string_at(&str, 7) == '\0');

        cspd_string_clear(&str);
        //! [Append string]
    }

    cspd_string str;
    cspd_string_init(&str);            // length = 5, capacity = 6
    cspd_string_append(&str, "hello"); // requires capacity = 6, i.e. "hello\0"

    cspd_assert(str.capacity == 16);
    cspd_assert(str.length == 5);

    cspd_assert(cspd_string_at(&str, 0) == 'h');
    cspd_assert(cspd_string_at(&str, 1) == 'e');
    cspd_assert(cspd_string_at(&str, 2) == 'l');
    cspd_assert(cspd_string_at(&str, 3) == 'l');
    cspd_assert(cspd_string_at(&str, 4) == 'o');
    cspd_assert(cspd_string_at(&str, 5) == '\0');

    cspd_string_append(&str, "world");

    cspd_assert(str.capacity == 16);
    cspd_assert(str.length == 10);

    cspd_assert(cspd_string_at(&str, 5) == 'w');
    cspd_assert(cspd_string_at(&str, 6) == 'o');
    cspd_assert(cspd_string_at(&str, 7) == 'r');
    cspd_assert(cspd_string_at(&str, 8) == 'l');
    cspd_assert(cspd_string_at(&str, 9) == 'd');
    cspd_assert(cspd_string_at(&str, 10) == '\0');

    // cspd_print_fn("%s", str.data);
    // Output: helloworld

    cspd_string_clear(&str);
}

static void test_concat(void)
{
    //! [Concat string]
    cspd_string str      = cspd_string_new("");
    cspd_string tmp      = cspd_string_new("hello");
    char        cstr[]   = "world";
    char        actual[] = "helloworld\0";

    const char *parts[]  = {
        tmp.data,
        cstr,
    };

    cspd_string_concat(&str, parts, sizeof(parts) / sizeof(parts[0]));
    cspd_string_clear(&tmp);

    // cspd_print_fn("%s", str.data);
    // Output: helloworld

    cspd_assert(str.capacity == 16);
    cspd_assert(str.length == 10);

    for (usize i = 0; i < strlen(actual); ++i) {
        cspd_assert(((char *)str.data)[i] == actual[i]);
    }

    cspd_string_clear(&str);
    //! [Concat string]
}

static void test_join(void)
{
    //! [Join string]
    cspd_string str      = cspd_string_new("");
    cspd_string tmp_a    = cspd_string_new("hello");
    cspd_string tmp_b    = cspd_string_new("world");

    char        sep      = ',';
    char        actual[] = "hello,world\0";
    const char *parts[]  = {
        tmp_a.data,
        tmp_b.data,
    };

    cspd_string_join(&str, sep, parts, sizeof(parts) / sizeof(parts[0]));

    cspd_string_clear(&tmp_a);
    cspd_string_clear(&tmp_b);

    cspd_assert(str.capacity == 16);
    cspd_assert(str.length == 11);

    for (usize i = 0; i < strlen(actual); ++i) {
        cspd_assert(((char *)str.data)[i] == actual[i]);
    }

    // cspd_print_fn("%s", str.data);
    // Output: hello,world

    cspd_string_clear(&str);
    //! [Join string]
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

static void ts_expect_impl(cspd_string *str, const char *actual)
{
    for (usize i = 0; i < strlen(actual); ++i) {
        cspd_assert(((char *)str->data)[i] == actual[i]);
    }
}
