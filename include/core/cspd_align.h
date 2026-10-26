/**
 * @file cspd_align.h
 * @brief Alignment calculation utilities.
 */

#ifndef CSPD_ALIGN_H
#define CSPD_ALIGN_H

#include "cspd_assert.h"
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

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_ALIGN_H
