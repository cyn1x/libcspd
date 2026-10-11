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

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Data structure for the string.
 *
 * The `capacity` refers to the amount of bytes consumed by the string, i.e. the
 * memory consumed. The `length` refers to the actual length of the string, not
 * including the null terminator.
 *
 * @var cspd_string::capacity
 * The size of the data in bytes, including the null terminator.
 *
 * @var cspd_string::length
 * The length of the string, not including the null terminator.
 *
 * @var cspd_string::data
 * Memory which has been allocated for the string to store data.
 */
typedef struct cspd_string_t
{
    usize capacity;
    usize length;
    char *data;
} cspd_string;

/**
 * @brief Initializes an uninitialized string.
 *
 * Initializes a string by reserving the required capacity from the given
 * length. The struct will be zero-initialized if `len` is `NULL` or `0`.
 *
 * @warning Should only be called once for an uninitialized string.
 *
 * @param str The pointer to the string to initialize.
 * @param len The amount of characters to reserve space for.
 *
 * @par Example
 * @code
 *   cspd_string str;
 *   cspd_string_init(&str);
 * @endcode
 */
CSPD_API void cspd_string_init(cspd_string *str, usize len);

/**
 * @brief Creates a new string.
 *
 * Creates a new string with the given character array.
 *
 * @param cstr The pointer to the string to initialize.
 *
 * @returns A new string.
 *
 * @par Example
 * @code
 *   cspd_string str;
 *   cspd_string_init(&str);
 * @endcode
 */
CSPD_API cspd_string cspd_string_new(char cstr[]);

/**
 * @brief Adds an array of characters to a string.
 *
 * Adds an array of characters to a string by using the available space before
 * allocating more memory.
 *
 * @param str The pointer to the string to initialize.
 * @param arr The pointer to the char array.
 * @param size The size of the char array.
 */
CSPD_API void cspd_string_append(cspd_string *str, char cstr[]);

/**
 * @brief Joins strings together.
 *
 * Concatenates strings in the order they are specified.
 *
 * @param str Pointer to the destination string.
 * @param parts Pointer to the array of strings.
 * @param count The number of strings to concatenate.
 */
CSPD_API void cspd_string_concat(cspd_string *str, char *parts[], usize count);

/**
 * @brief Joins strings together using a separator character.
 *
 * Sequentially joins strings and separates them with the specified delimiter.
 *
 * @param str Pointer to the destination string.
 * @param count The number of strings to join.
 * @param parts Pointer to the array of strings.
 * @param sep The separator to place between each string.
 */
CSPD_API void cspd_string_join(cspd_string *str, char delim, char *parts[],
                               usize count);

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
 * @brief Retrieves the character at the specified index.
 *
 * Returns a read-only (i.e. the value, not reference) copy of the character at
 * the index position.
 *
 * @warning Should be called when a string is no longer required to prevent
 * memory leaks.
 *
 * @param str Pointer to the string.
 * @param idx The index to retrieve.
 */
static inline char cspd_string_at(cspd_string *str, u32 idx)
{
    return ((char *)str->data)[idx];
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_STRING_H
