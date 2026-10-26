/**
 * @file cspd_util
 * @brief General utilities and helpers.
 *
 * Contains general utilities that are not semantically suited to other
 * translation units in the library.
 */

#ifndef CSPD_UTIL_H
#define CSPD_UTIL_H

#include "cspd_types.h"

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

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_UTIL_H
