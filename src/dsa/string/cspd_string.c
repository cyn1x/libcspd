#define CSPD_EXPORTS

#include "cspd_string.h"
#include "cspd_assert.h"
#include "cspd_mem.h"
#include "cspd_util.h"

/**
 * @brief Minimum capacity of the string.
 *
 * Any allocation smaller than this value is raised to this value.
 */
#define MIN_SIZE 16

/**
 * @brief Capacity granularity in bytes.
 *
 * Allocation sizes are rounded up to a multiple of this value.
 *
 * @note Must be a power of two, as the rounding uses a bitmask.
 */
#define QUANT 16

// Enforce the power-of-two requirement documented on QUANT.
_Static_assert((QUANT & (QUANT - 1)) == 0, "QUANT must be a power of two");

void cspd_string_init(cspd_string *str)
{
    cspd_assert(str != NULL);

    str->capacity = 0;
    str->length   = 0;
    str->data     = NULL;

    usize len     = MIN_SIZE - 1;
    usize size    = (sizeof(char) * len) + 1;
    str->data     = cspd_calloc(size, sizeof(char));

    if (str->data) {
        str->capacity = size;
    }
}

cspd_string cspd_string_new(char *cstr)
{
    cspd_string str;

    usize       len  = strlen(cstr);
    usize       size = (sizeof(char) * len) + 1;

    if (len < MIN_SIZE) {
        size = QUANT;
        cspd_string_init(&str);
    } else {
        size     = cspd_quant_up(size, QUANT);
        str.data = cspd_malloc(size);
    }

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

void cspd_string_join(cspd_string *str, char delim, char *parts[], usize count)
{
    usize len = count - 1; // One delimiter between each pair
    for (usize i = 0; i < count; ++i) {
        len += strlen(parts[i]);
    }

    usize size = (sizeof(char) * len) + 1;
    if (str->length + len >= str->capacity) {
        cspd_string_reserve(str, str->capacity + size);
    }

    char *dst = str->data + str->length;
    for (usize i = 0; i < count; ++i) {
        if (i > 0) {
            *dst++ = delim;
        }
        usize amt = strlen(parts[i]);
        memcpy(dst, parts[i], amt);
        dst += amt;
    }

    *dst++ = '\0';
    str->length += len;
}

void cspd_string_reserve(cspd_string *str, usize size)
{
    if (size <= str->capacity) return;

    usize dbl = str->capacity * 2;
    if (size < dbl) size = dbl;

    size      = cspd_quant_up(size, QUANT);

    char *blk = cspd_realloc(str->data, size);
    if (!blk) {
        // TODO: #0034 - Error handling
        return;
    }
    str->data     = blk;
    str->capacity = size;
}

void cspd_string_clear(cspd_string *str)
{
    cspd_free(str->data);
    str->capacity = 0;
    str->length   = 0;
    str->data     = NULL;
}
