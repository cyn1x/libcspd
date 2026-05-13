/**
 * @file defs.test.h
 */

#ifndef CSPD_DEFS_TEST_H
#define CSPD_DEFS_TEST_H

#include <cspd_cmp.h>
#include <cspd_types.h>

//! [Comparator type initialization]
cspd_cmp(int8) cspd_cmp(int16) cspd_cmp(int32) cspd_cmp(int64) cspd_cmp(uint8)
    cspd_cmp(uint16) cspd_cmp(uint32) cspd_cmp(uint64)
//! [Comparator type initialization]

#endif // CSPD_DEFS_TEST_H
