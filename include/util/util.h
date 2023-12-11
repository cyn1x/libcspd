/**
 * @file util.h
 */

/**
 *@fn swap(void *pa, void *pb, size_t size)
 *
 * @brief Performs an in-place bytewise swap between two pointers.
 *
 * Performs an in-place bytewise swap between two pointers.
 *
 * @param
 */

#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <types.h>

void swap(void *pa, void *pb, size_t size);

#endif // UTIL_H
