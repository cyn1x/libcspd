#define CSPD_EXPORTS

#include "cspd_mem.h"
#include <stdlib.h>

/**
 * @internal
 *
 * @brief Default malloc function.
 *
 * Allocate memory using the C standard library implementation in `stdlib.h`
 * by calling `malloc`.
 *
 * @param size Size in bytes to allocate.
 *
 * @return Pointer to allocated memory, or `NULL` on failure.
 *
 * @see
 * https://en.wikipedia.org/wiki/C_dynamic_memory_allocation#Overview_of_functions
 */
static void *real_malloc(usize size);

/**
 * @internal
 *
 * @brief Default calloc function.
 *
 * Allocate memory using the C standard library implementation in `stdlib.h`
 * by calling `calloc`.
 *
 * @param usize Number of elements to allocate.
 * @param usize Size in bytes of each element.
 *
 * @return Pointer to allocated memory, or `NULL` on failure.
 *
 * @see
 * https://en.wikipedia.org/wiki/C_dynamic_memory_allocation#Overview_of_functions
 */
static void *real_calloc(usize number, usize size);

/**
 * @internal
 *
 * @brief Default realloc function.
 *
 * Reallocate memory using the C standard library implementation in `stdlib.h`
 * by calling `realloc`.
 *
 * @param void Pointer to a previously allocated block of memory.
 * @param usize Size in bytes of the new block.
 *
 * @return Pointer to the reallocated memory, or `NULL` on failure.
 *
 * @see
 * https://en.wikipedia.org/wiki/C_dynamic_memory_allocation#Overview_of_functions
 */
static void *real_realloc(void *block, usize size);

/**
 * @internal
 *
 * @brief Default free function.
 *
 * Free memory using the C standard library implementation in `stdlib.h` by
 * calling `free`.
 *
 * @param void Pointer to a previously allocated block of memory.
 *
 * @see
 * https://en.wikipedia.org/wiki/C_dynamic_memory_allocation#Overview_of_functions
 */
static void real_free(void *block);

/**
 * @brief Data structure encapsulating callbacks to memory functions.
 *
 * @var mem::cspd_malloc_func
 * Callback function for malloc.
 *
 * @var mem::cspd_calloc_func
 * Callback function for calloc.
 *
 * @var mem::cspd_realloc_func
 * Callback function for realloc.
 *
 * @var mem::cspd_free_func
 * Callback function for free.
 */
static struct
{
    cspd_malloc_func  malloc_func;
    cspd_calloc_func  calloc_func;
    cspd_realloc_func realloc_func;
    cspd_free_func    free_func;
} mem = {real_malloc, real_calloc, real_realloc, real_free};

void cspd_get_mem_functions(cspd_malloc_func  *malloc_func,
                            cspd_calloc_func  *calloc_func,
                            cspd_realloc_func *realloc_func,
                            cspd_free_func    *free_func)
{
    *malloc_func  = mem.malloc_func;
    *calloc_func  = mem.calloc_func;
    *realloc_func = mem.realloc_func;
    *free_func    = mem.free_func;
}

void cspd_set_mem_functions(cspd_malloc_func  malloc_func,
                            cspd_calloc_func  calloc_func,
                            cspd_realloc_func realloc_func,
                            cspd_free_func    free_func)
{
    mem.malloc_func  = malloc_func;
    mem.calloc_func  = calloc_func;
    mem.realloc_func = realloc_func;
    mem.free_func    = free_func;
}

void *cspd_malloc(usize size)
{
    return mem.malloc_func(size);
}

void *cspd_calloc(usize number, usize size)
{
    return mem.calloc_func(number, size);
}

void *cspd_realloc(void *block, usize size)
{
    return mem.realloc_func(block, size);
}

void cspd_free(void *block)
{
    mem.free_func(block);
}

static void *real_malloc(usize size)
{
    return malloc(size);
}

static void *real_calloc(usize number, usize size)
{
    return calloc(number, size);
}

static void *real_realloc(void *block, usize size)
{
    return realloc(block, size);
}

static void real_free(void *block)
{
    free(block);
}
