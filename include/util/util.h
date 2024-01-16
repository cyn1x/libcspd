/**
 * @file util.h
 * General utilities not specific to the purpose of any other header file.
 */

/**
 * @fn swap(void *pa, void *pb, size_t size)
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

/**
 * @fn print_binary(void *data, size_t size)
 *
 * @brief Prints out the binary representation of the given data.
 *
 * Uses the data and the provided data size in bytes to print out a binary
 * respresentation of the given data.
 *
 * @param data The data to show the binary representation of.
 * @param size The size of the data type in bytes.
 */

#ifndef UTIL_H
#define UTIL_H

#include "defs.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void             swap(void *pa, void *pb, size_t size);
LIBCSPD_API void print_binary(void *data, size_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UTIL_H
