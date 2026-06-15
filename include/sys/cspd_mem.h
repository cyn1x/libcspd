/**
 * @file cspd_mem.h
 */

/**
 * @typedef *cspd_malloc_func
 *
 * @brief Callback function type `cspd_malloc_func`.
 */

/**
 * @typedef *cspd_calloc_func
 *
 * @brief Callback function type `cspd_calloc_func`.
 */

/**
 * @typedef *cspd_realloc_func
 *
 * @brief Callback function type `cspd_realloc_func`.
 */

/**
 * @typedef *cspd_free_func
 *
 * @brief Callback function type `cspd_free_func`.
 */

/**
 * @fn void void cspd_get_mem_functions (cspd_malloc_func *malloc_func,
 * cspd_calloc_func *calloc_func, cspd_realloc_func *realloc_func,
 * cspd_free_func *free_func)
 *
 * @brief Retrieves the currently configured memory functions.
 *
 * Stores the addresses of the current configured memory functions to the
 * corresponding pointers passed in by the caller. Any parameter may be `NULL`.
 *
 * @param malloc_func Pointer to store the address of the currently configured
 * allocator function
 * @param calloc_func Pointer to store the address of the currently configured
 * contiguous allocator function
 * @param realloc_func Pointer to store the address of the currently configured
 * reallocator function
 * @param free_func Pointer to store the address of the currently configured
 * memory release function
 *
 * @sa cspd_set_mem_functions
 */

/**
 * @fn void cspd_set_mem_functions (cspd_malloc_func malloc_func,
 * cspd_calloc_func calloc_func, cspd_realloc_func  realloc_func,
 * cspd_free_func free_func)
 *
 * @brief Overrides the default memory functions.
 *
 * Optional override for the implementer to set a custom memory allocator. All
 * of the parameters must be set. At the very least, this function should be
 * called before any memory allocations are made. Ideally, custom memory
 * functions should be set before anything else is called in the library.
 *
 * @param malloc_func Function pointer to the memory allocator function
 * @param calloc_func Function pointer to the contiguous allocator function
 * @param realloc_func Function pointer to the reallocator function
 * @param free_func Function pointer to the memory release function
 *
 * @returns `true` on success or `false` on failure.
 *
 * @sa cspd_get_mem_functions
 */

/**
 * @fn void *cspd_malloc(size_t size)
 *
 * @internal
 *
 * @brief Allocates memory using the currently configured allocator.
 *
 * Defaults to the `malloc` implementation in the C standard library
 * if no memory allocator has been defined by the library implementer.
 *
 * @param size Size in of bytes.
 * @return Pointer to allocated memory, or `NULL` on failure.
 *
 * @see https://en.wikipedia.org/wiki/C_standard_library
 */

/**
 * @fn *cspd_calloc(size_t number, size_t size)
 *
 * @internal
 *
 * @brief Allocates blocks of memory using the currently configured allocator.
 *
 * Defaults to the default implementation of `calloc` in the C standard library
 * if no memory allocator has been defined by the library implementer.
 *
 * @param size_t Number of elements to allocate.
 * @param size_t Size in bytes of each element.
 *
 * @return Pointer to allocated memory, or `NULL` on failure.
 *
 * @see https://en.wikipedia.org/wiki/C_standard_library
 */

/**
 * @fn *cspd_realloc(void *block, size_t size)
 *
 * @internal
 *
 * @brief Reallocates a block of memory using the currently configured
 * reallocator.
 *
 * Defaults to the default implementation of `realloc` in the C standard library
 * if no memory reallocator has been defined by the library implementer.
 *
 * @param void Pointer to a previously allocated block of memory.
 * @param size_t Size in bytes of the new block.
 *
 * @return Pointer to the reallocated memory, or `NULL` on failure.
 *
 * @see https://en.wikipedia.org/wiki/C_standard_library
 */

/**
 * @fn cspd_free(void *block)
 *
 * @internal
 *
 * @brief Reallocates a block of memory using the currently configured
 * reallocator.
 *
 * Defaults to the default implementation of `free` in the C standard library
 * if no memory free function has been defined by the library implementer.
 *
 * @param void Pointer to a previously allocated block of memory.
 *
 * @see https://en.wikipedia.org/wiki/C_standard_library
 */

#ifndef CSPD_MEM_H
#define CSPD_MEM_H

#include "cspd_defs.h"
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef void *(*cspd_malloc_func)(size_t size);
typedef void *(*cspd_calloc_func)(size_t number, size_t size);
typedef void *(*cspd_realloc_func)(void *block, size_t size);
typedef void (*cspd_free_func)(void *block);

CSPD_API void cspd_get_mem_functions(cspd_malloc_func  *malloc_func,
                                     cspd_calloc_func  *calloc_func,
                                     cspd_realloc_func *realloc_func,
                                     cspd_free_func    *free_func);
CSPD_API void cspd_set_mem_functions(cspd_malloc_func  malloc_func,
                                     cspd_calloc_func  calloc_func,
                                     cspd_realloc_func realloc_func,
                                     cspd_free_func    free_func);
void         *cspd_malloc(size_t size);
void         *cspd_calloc(size_t number, size_t size);
void         *cspd_realloc(void *block, size_t size);
void          cspd_free(void *block);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CSPD_MEM_H
