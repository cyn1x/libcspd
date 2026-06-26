/**
 * @file cspd_defs.test.h
 */

#ifndef CSPD_DEFS_TEST_H
#define CSPD_DEFS_TEST_H

#include <cspd_cmp.h>
#include <cspd_types.h>

//! [Comparator type initialization]
cspd_cmp(i8) cspd_cmp(i16) cspd_cmp(i32) cspd_cmp(i64) cspd_cmp(u8)
    cspd_cmp(u16) cspd_cmp(u32) cspd_cmp(u64)
//! [Comparator type initialization]

#endif // CSPD_DEFS_TEST_H
