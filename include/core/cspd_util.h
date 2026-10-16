/**
 * @file cspd_util
 * @brief General utilities and helpers.
 *
 * Contains general utilities that are not semantically suited to other
 * translation units in the library.
 */

#ifndef CSPD_UTIL_H
#define CSPD_UTIL_H

#include "cspd_exports.h"
#include "cspd_types.h"

#ifdef __clang__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @internal
 *
 * @brief Performs an in-place bytewise swap between two pointers.
 *
 * Iterates through each byte of the given size in bytes and performs an
 * in-place bytewise swap of each byte.
 *
 * @param pa Pointer to the first data type.
 * @param pb Pointer to the second data type.
 * @param size The size of the data types in bytes.
 */
void cspd_swap(void *pa, void *pb, usize size);

/**
 * @brief Prints out the binary representation of the given data.
 *
 * Uses the data and the provided data size in bytes to print out a binary
 * respresentation of the given data.
 *
 * @param data The data to show the binary representation of.
 * @param size The size of the data type in bytes.
 */
CSPD_API void cspd_print_binary(void *data, usize size);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_UTIL_H
