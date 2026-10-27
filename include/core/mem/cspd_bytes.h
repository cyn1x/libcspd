/**
 * @file cspd_bytes.h
 * @brief Memory manipulation.
 */

#ifndef CSPD_BYTES_H
#define CSPD_BYTES_H

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
void cspd_memswap(void *pa, void *pb, usize size);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_BYTES_H
