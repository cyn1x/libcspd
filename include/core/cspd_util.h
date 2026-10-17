/**
 * @file cspd_util
 * @brief General utilities and helpers.
 *
 * Contains general utilities that are not semantically suited to other
 * translation units in the library.
 */

#ifndef CSPD_UTIL_H
#define CSPD_UTIL_H

#include "cspd_assert.h"
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
 * @internal
 *
 * @brief Rounds a size up to the next multiple of a power of two.
 *
 * Rounds the byte count @p size up so that it is a multiple of @p quant.
 *
 * @note This is a size operation and does not control where an allocation is
 * placed.
 *
 * @param size The size in bytes to round up.
 * @param quant The granularity in bytes. Must be a power of two.
 *
 * @returns The smallest multiple of @p quant that is `>= size`.
 */
static inline usize cspd_quant_up(usize size, usize quant)
{
    cspd_assert(quant != 0 && (quant & (quant - 1)) == 0);
    return (size + quant - 1) & ~(quant - 1);
}

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
