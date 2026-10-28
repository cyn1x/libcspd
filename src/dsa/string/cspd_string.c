#define CSPD_EXPORTS

#include "cspd_string.h"
#include "cspd_align.h"
#include "cspd_assert.h"
#include "cspd_mem.h"

/**
 * @internal
 *
 * @brief Capacity granularity in bytes.
 *
 * Allocation sizes are rounded up to a multiple of this value.
 *
 * @note Must be a power of two, as the rounding uses a bitmask.
 */
#define QUANT 16

// Enforce the power-of-two requirement documented on QUANT.
_Static_assert((QUANT & (QUANT - 1)) == 0, "QUANT must be a power of two");

/**
 * @internal
 *
 * @brief Resets to an empty inline string.
 *
 * Zero initializes the entire data structure and sets the flag bit to indicate
 * it is an inline string.
 *
 * @note Does not free memory.
 */
static void reset(cspd_string *str);

/**
 * @internal
 *
 * @brief Copies the inline string to the heap.
 *
 * Copies the bytes consumed by the inline storage buffer to heap allocated
 * memory.
 *
 * @param dst Pointer to the destination string.
 * @param len Precalculated length in bytes of the string.
 * @param amt Amount of bytes to copy to the heap.
 */
static void copy_inline_buffer_to_heap(cspd_string *dst, usize len, usize amt);

void cspd_string_init(cspd_string *str)
{
    cspd_assert(str != NULL);

    reset(str);
}

cspd_string cspd_string_new(const char *cstr)
{
    cspd_string str;

    usize len  = strlen(cstr);
    usize size = (sizeof(u8) * len) + 1;

    if (len < CSPD_STRING_INLINE_SIZE - 1) {
        // Fits in the inline buffer, so no heap allocation
        cspd_string_init(&str);

        // Obtain the most significant bit (MSB) to store metadata
        usize idx  = CSPD_STRING_META_BYTE;
        u8   *byte = &(str.buffer[sizeof(u8) * idx]); // MSB
        *byte |= 0x80;
        *byte |= len;

        // Copy the data to the buffer and set the NUL terminator
        memcpy(str.buffer, cstr, size);
        str.buffer[CSPD_STRING_INLINE_LEN] = '\0';

        return str;
    }

    size     = cspd_quant_up(size, QUANT);
    str.data = cspd_malloc(size * sizeof(u8));

    if (str.data) {
        str.length   = len;
        str.capacity = size;
        memcpy(str.data, cstr, size);
        str.data[str.length + 1] = '\0';
    }

    return str;
}

void cspd_string_append(cspd_string *str, const char cstr[])
{
    bool  inlined = cspd_string_is_inline(str);
    usize idx     = cspd_string_length(str); // Length byte offset
    usize amt     = strlen(cstr);
    usize len     = idx + amt;
    usize size    = (sizeof(char) * amt) + 1;

    if (inlined && len < CSPD_STRING_INLINE_SIZE - 1) {
        // Still fits in the inline buffer, so no heap allocation required
        usize meta = CSPD_STRING_META_BYTE;
        u8   *byte = &(str->buffer[sizeof(u8) * meta]); // MSB

        *byte += (u8)amt;
        memcpy(str->buffer + idx, cstr, size);

        return;
    }

    if (inlined && len >= CSPD_STRING_INLINE_SIZE - 1) {
        // Inline buffer overflow detected
        copy_inline_buffer_to_heap(str, idx, len);
    }

    if (str->length + amt >= str->capacity) {
        cspd_string_reserve(str, str->capacity + size);
    }

    str->length += amt;
    memcpy(str->data + idx, cstr, size);
    str->data[str->length + 1] = '\0';
}

void cspd_string_join(cspd_string *str, char delim, const char *parts[],
                      usize count)
{
    usize amt = count - 1; // One delimiter between each pair
    for (usize i = 0; i < count; ++i) {
        amt += strlen(parts[i]);
    }

    bool  inlined = cspd_string_is_inline(str);
    usize idx     = cspd_string_length(str); // Length byte offset
    usize len     = idx + amt;               // Required length in bytes
    u8   *dst     = NULL;

    if (inlined && len < CSPD_STRING_INLINE_SIZE - 1) {
        // Still fits in the inline buffer, so no heap allocation required
        usize meta = CSPD_STRING_META_BYTE;
        u8   *byte = &(str->buffer[sizeof(u8) * meta]); // MSB
        *byte += (u8)amt;
        dst = str->buffer;
    }
    else {
        // Heap allocation required
        if (inlined && len >= CSPD_STRING_INLINE_SIZE - 1) {
            // Inline buffer overflow detected
            copy_inline_buffer_to_heap(str, idx, len);
        }
        else {
            // Buffer is already on the heap
            usize size = (sizeof(char) * amt) + 1;
            if (str->length + amt >= str->capacity) {
                cspd_string_reserve(str, str->capacity + size);
            }
        }
        dst = str->data + str->length;

        // Preset length and terminate before copy
        str->length += amt;
        str->data[str->length + 1] = '\0';
    }

    for (usize i = 0; i < count; ++i) {
        if (i > 0) {
            *dst++ = delim;
        }
        amt = strlen(parts[i]);
        memcpy(dst, parts[i], amt);
        dst += amt;
    }
    *dst++ = '\0';
}

void cspd_string_reserve(cspd_string *str, usize size)
{
    if (size <= str->capacity) return;

    usize dbl = str->capacity * 2;
    if (size < dbl) size = dbl;

    size    = cspd_quant_up(size, QUANT);

    u8 *blk = cspd_realloc(str->data, size);
    if (!blk) {
        // TODO: #0034 - Error handling
        return;
    }
    str->data     = blk;
    str->capacity = size;
}

void cspd_string_clear(cspd_string *str)
{
    cspd_assert(str != NULL);

    if (!cspd_string_is_inline(str)) {
        cspd_free(str->data);
    }

    reset(str);
}

static void copy_inline_buffer_to_heap(cspd_string *dst, usize len, usize amt)
{
    usize size  = cspd_quant_up(amt, QUANT);
    void *block = cspd_malloc(size * sizeof(u8));
    if (!block) return;

    // Copy inline buffer onto the heap
    memcpy(block, dst->buffer, sizeof(u8) * amt + 1);

    // Assign memory pointer to the string data structure
    dst->data          = block;
    dst->data[len + 1] = '\0';
    dst->length        = len;
    dst->capacity      = size;
}

static void reset(cspd_string *str)
{
    memset(str, 0, sizeof *str);
    str->buffer[CSPD_STRING_META_BYTE] = 0x80;
}
