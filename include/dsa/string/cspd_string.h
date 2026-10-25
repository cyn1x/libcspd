/**
 * @file cspd_string.h
 * @brief Data structures and algorithms for representing words and sentences.
 *
 * @see https://en.wikipedia.org/wiki/String_(computer_science)
 */

#ifndef CSPD_STRING_H
#define CSPD_STRING_H

#include "cspd_exports.h"
#include "cspd_types.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*
 * Inline layout: buffer[CSPD_STRING_INLINE_SIZE] is the flag/length byte.
 *   bit 7 (0x80): set = inline, clear = heap
 *   bits 0-6 (0x7F): inline length, max length of CSPD_STRING_INLINE_LEN
 */

/**
 * @internal
 *
 * @brief Maximum size in bytes for an inline string.
 */
#define CSPD_STRING_INLINE_SIZE 24

/**
 * @brief Data structure for the string.
 *
 * Hybrid string data structure that supports inline and memory allocated
 * strings.
 *
 * @var cspd_string::capacity
 * The amount of bytes consumed by the string, including the null terminator.
 *
 * @var cspd_string::length
 * The length of the string, not including the null terminator.
 *
 * @var cspd_string::data
 * Memory which has been allocated for the string to store data.
 *
 * @var cspd_string::buffer
 * Short string inline buffer for strings that do not require an alloc.
 *
 * @see https://en.wikipedia.org/wiki/Union_type
 */
typedef union cspd_string_t
{
    struct
    {
        usize capacity;
        usize length;
        u8   *data;
    };
    u8 buffer[CSPD_STRING_INLINE_SIZE];
} cspd_string;

_Static_assert(sizeof(cspd_string) == CSPD_STRING_INLINE_SIZE,
               "cspd_string must stay 24 bytes (x64 SSO layout)");
_Static_assert(offsetof(cspd_string, length) == 8,
               "cspd_string: length must follow capacity (x64)");
_Static_assert(offsetof(cspd_string, data) == 16,
               "cspd_string: data must follow length (x64)");

/**
 * @internal
 *
 * @brief Index used to obtain the metadata byte in the inline string buffer.
 */
#define CSPD_STRING_META_BYTE (CSPD_STRING_INLINE_SIZE - 1)

_Static_assert((CSPD_STRING_META_BYTE) == sizeof(cspd_string) - 1,
               "flag/length byte must be the last byte of the inline buffer");

/**
 * @internal
 *
 * @brief Maximum length permitted for an inline string.
 *
 * @note Does not include the NUL terminator.
 */
#define CSPD_STRING_INLINE_LEN (CSPD_STRING_INLINE_SIZE - 2)

_Static_assert(
    (CSPD_STRING_INLINE_LEN) == CSPD_STRING_META_BYTE - 1,
    "inline max length is 24 bytes minus the NUL and the flag/length byte");
_Static_assert(CSPD_STRING_INLINE_LEN <= 0x7Fu,
               "inline max length must fit in the length bits");

/**
 * @brief Initializes an uninitialized string.
 *
 * Zero initializes the entire data structure and sets the initial state to an
 * empty inline string.
 *
 * @note Does not pre-emptively allocate memory.
 *
 * @param str The pointer to the string to initialize.
 *
 * @par Example
 * @code
 *   cspd_string str;
 *   cspd_string_init(&str);
 * @endcode
 */
CSPD_API void cspd_string_init(cspd_string *str);

/**
 * @brief Creates a new string.
 *
 * Creates a new string with the given character array.
 *
 * @param cstr The pointer to the string to initialize.
 *
 * @returns A new string containing the given sequence of characters.
 *
 * @par Example
 * @code
 *   cspd_string str = cspd_string_new("hello,world");
 *   cspd_print_fn("%s", str.data);
 *   // Output: hello,world
 * @endcode
 */
CSPD_API cspd_string cspd_string_new(const char *cstr);

/**
 * @brief Adds an array of characters to a string.
 *
 * Adds an array of characters to a string by using the available space before
 * allocating more memory.
 *
 * @param str The pointer to the string to initialize.
 * @param arr The pointer to the char array.
 * @param size The size of the char array.
 *
 * @snippet cspd_string.test.c Append string
 */
CSPD_API void cspd_string_append(cspd_string *str, const char cstr[]);

/**
 * @brief Joins strings together using a separator character.
 *
 * Joins strings in the order they are specified and separates them with the
 * given delimiter character.
 *
 * @param str Pointer to the destination string.
 * @param count The number of strings to join.
 * @param parts Pointer to the array of strings.
 * @param delim The separator to place between each string.
 *
 * @snippet cspd_string.test.c Join string
 */
CSPD_API void cspd_string_join(cspd_string *str, const char delim,
                               const char *parts[], usize count);

/**
 * @brief Resizes a string.
 *
 * Reserves the required space for a string.
 *
 * @info Use to reserve space ahead of time to prevent repetitive memory
 * allocations.
 *
 * @param str Pointer to the string to be resized.
 * @param size The new size in bytes.
 */
CSPD_API void cspd_string_reserve(cspd_string *str, usize size);

/**
 * @brief Deletes a string.
 *
 * Removes all characters from a string by freeing the allocated memory.
 *
 * @warning This function should be called after the string is no longer
 * required to prevent memory leaks.
 *
 * @param str The pointer to the string to be deleted.
 */
CSPD_API void cspd_string_clear(cspd_string *str);

/**
 * @brief Joins two or more strings together.
 *
 * Concatenates strings in the order they are specified.
 *
 * @param str Pointer to the destination string.
 * @param parts Pointer to the array of strings.
 * @param count The number of strings to concatenate.
 *
 * @snippet cspd_string.test.c Concat string
 */
static inline void cspd_string_concat(cspd_string *str, const char *parts[],
                                      usize count)
{
    for (usize i = 0; i < count; ++i) {
        cspd_string_append(str, parts[i]);
    }
}

/**
 * @brief Determines if the string is inlined.
 *
 * Checks whether the string is stored on the heap or inline, and returns the
 * result.
 *
 * @returns `true` if the string is inline, otherwise `false`.
 */
static inline bool cspd_string_is_inline(const cspd_string *str)
{
    return str->buffer[CSPD_STRING_META_BYTE] & 0x80;
}

/**
 * @brief Gets the length of the string.
 *
 * Retrieves the string length in bytes by checking the metadata byte if using
 * the inline storage buffer, otherwise the assigned length via
 * `cspd_string::length` if using heap storage.
 *
 * @returns The length of the string.
 */
static inline usize cspd_string_length(const cspd_string *str)
{
    return cspd_string_is_inline(str)
               ? (usize)(str->buffer[CSPD_STRING_META_BYTE] & 0x7Fu)
               : str->length;
}

/**
 * @brief Retrieves the character at the specified index.
 *
 * Returns a read-only (i.e. the value, not reference) copy of the character at
 * the index position.
 *
 * @param str Pointer to the string.
 * @param idx The index to retrieve.
 *
 * returns The character at the specified index.
 */
static inline char cspd_string_at(cspd_string *str, u32 idx)
{
    return cspd_string_is_inline(str) ? str->buffer[idx]
                                      : ((char *)str->data)[idx];
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_STRING_H
