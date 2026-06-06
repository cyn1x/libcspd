/**
 * @file cspd_mem.h
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
