/**
 * @file cspd_types.h
 * Custom type definitions.
 * More readable type definitions for types in `stdint.h`.
 */

#ifndef CSPD_TYPES_H
#define CSPD_TYPES_H

#include <stdint.h>

typedef int (*cspd_cmp)(const void *, const void *);

typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;
typedef int64_t  int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#endif // CSPD_TYPES_H
