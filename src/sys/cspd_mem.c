#define CSPD_EXPORTS

#include "cspd_mem.h"

/**
 * @internal
 *
 * @brief
 *
 *
 *
 * @param
 *
 * @returns
 */
static void *real_malloc(size_t size);

/**
 * @internal
 *
 * @brief
 *
 *
 *
 * @param
 *
 * @returns
 */
static void *real_calloc(size_t number, size_t size);

/**
 * @internal
 *
 * @brief
 *
 *
 *
 * @param
 *
 * @returns
 */
static void *real_realloc(void *block, size_t size);

/**
 * @internal
 *
 * @brief
 *
 *
 *
 * @param
 *
 * @returns
 */
static void real_free(void *block);

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

void *cspd_malloc(size_t size)
{
    return mem.malloc_func(size);
}

void *cspd_calloc(size_t number, size_t size)
{
    return mem.calloc_func(number, size);
}

void *cspd_realloc(void *block, size_t size)
{
    return mem.realloc_func(block, size);
}

void cspd_free(void *block)
{
    mem.free_func(block);
}

static void *real_malloc(size_t size)
{
    return malloc(size);
}

static void *real_calloc(size_t number, size_t size)
{
    return calloc(number, size);
}

static void *real_realloc(void *block, size_t size)
{
    return realloc(block, size);
}

static void real_free(void *block)
{
    free(block);
}
