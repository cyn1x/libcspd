#define CSPD_EXPORTS

#include "cspd_string.h"
#include "cspd_assert.h"
#include "cspd_mem.h"
#include <string.h>

void cspd_string_init(cspd_string *str, usize len)
{
    cspd_assert(str != NULL);

    str->capacity = 0;
    str->length   = 0;
    str->data     = NULL;

    if (len == 0) return;

    usize size = (sizeof(char) * len) + 1;
    str->data  = cspd_calloc(size, sizeof(char));

    if (str->data) {
        str->capacity = size;
    }
}

cspd_string cspd_string_new(char cstr[])
{
    cspd_string str;
    str.capacity = 0;
    str.length   = 0;
    str.data     = NULL;

    usize len    = strlen(cstr);
    usize size   = (sizeof(char) * len) + 1;

    if (len == 0) return str;

    str.data = cspd_malloc(size);

    if (str.data) {
        str.length   = len;
        str.capacity = size;
        memcpy(str.data, cstr, size);
    }

    return str;
}

void cspd_string_append(cspd_string *str, char cstr[])
{
    usize len  = strlen(cstr);
    usize size = (sizeof(char) * len) + 1;
    usize idx  = str->length;

    if (str->length + len >= str->capacity) {
        cspd_string_reserve(str, str->capacity + size);
    }

    memcpy((char *)str->data + idx, cstr, size);
    str->length += len;
}

void cspd_string_concat(cspd_string *str, char *parts[], usize count)
{
    for (usize i = 0; i < count; ++i) {
        cspd_string_append(str, parts[i]);
    }
}

void cspd_string_join(cspd_string *str, char sep, char *parts[], usize count)
{
}

void cspd_string_reserve(cspd_string *str, usize size)
{
    str->data = cspd_realloc(str->data, sizeof(char) * size);
    if (!str->data) {
        // TODO: Handle error
    }
    str->capacity += size;
}

void cspd_string_clear(cspd_string *str)
{
    cspd_free(str->data);
    cspd_assert(errno == 0);
    str->capacity = 0;
    str->length   = 0;
    str->data     = NULL;
}
