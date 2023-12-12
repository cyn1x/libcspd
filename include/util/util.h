/**
 * @file util.h
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
 * @fn swap(void *data, size_t size)
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

#include "types.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef _WIN32
#ifdef LIBCSPD_EXPORTS
#define LIBCSPD_API __declspec(dllexport)
#else
#define LIBCSPD_API __declspec(dllimport)
#endif // LIBCSPD_EXPORTS
#elif __linux__
#define LIBCSPD_API __attribute__((visibility("default")))
#else
#define LIBCSPD_API
#endif // _WIN32

void             swap(void *pa, void *pb, size_t size);
LIBCSPD_API void print_binary(void *data, size_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UTIL_H
