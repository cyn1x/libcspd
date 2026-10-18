/**
 * @file cspd.h
 *
 * @brief Includes all core library modules.
 *
 * Provides an easy method of including all core modules and data structures for
 * leveraging the entire library.
 */

#ifndef CSPD_H
#define CSPD_H

// IWYU pragma: begin_exports

/*
 * Core
 */
#include "cspd_assert.h"
#include "cspd_cmp.h"
#include "cspd_mem.h"
#include "cspd_print.h"
#include "cspd_types.h"
#include "cspd_util.h"

/*
 * Data Structures & Algorithms
 */
#include "cspd_bstree.h"
#include "cspd_btree.h"
#include "cspd_llist.h"
#include "cspd_queue.h"
#include "cspd_stack.h"
#include "cspd_string.h"
#include "cspd_vector.h"

// IWYU pragma: end_exports

#endif // CSPD_H
