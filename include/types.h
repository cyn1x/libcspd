/**
 * @file types.h
 * Custom type definitions.
 * More readable type definitions for types in `stdint.h`.
 */

#ifndef TYPES_H
#define TYPES_H

#ifdef _WIN32
#pragma warning(disable : 5045)
#endif // _WIN32

#include <stdint.h>

typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;
typedef int64_t  int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#endif // TYPES_H
