/**
 * @file cspd_types.h
 * Custom type definitions.
 * Type definition aliases for C data types.
 *
 * @see https://en.wikipedia.org/wiki/C_data_types
 */

#ifndef CSPD_TYPES_H
#define CSPD_TYPES_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

typedef int (*cspd_cmp)(const void *, const void *);

typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef float_t   f32;
typedef double_t  f64;

typedef size_t    usize;
typedef ptrdiff_t isize;

#endif // CSPD_TYPES_H
