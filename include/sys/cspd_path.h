/**
 * @file cspd_path.h
 * @brief File system path utilities.
 *
 * Contains utilities for traversing file systems.
 */

#ifndef CSPD_PATH_H
#define CSPD_PATH_H

#include "cspd_exports.h"
#include "cspd_types.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief
 */
CSPD_API usize cspd_path_dirname(char *dst, usize dst_size, const char *src,
                                 usize src_len);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !CSPD_PATH_H
