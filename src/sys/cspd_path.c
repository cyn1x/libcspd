#define CSPD_EXPORTS

#include "cspd_path.h"
#include "cspd_assert.h"
#include "cspd_bytes.h"

/**
 * @internal
 *
 * @brief
 */
static bool is_separator(char c)
{
#ifdef _WIN32
    return c == '\\' || c == '/';
#else
    return c == '/';
#endif
}

usize cspd_path_dirname(char *dst, usize dst_size, const char *src,
                        usize src_len)
{
    cspd_assert(src != NULL);

    usize len = 0;
    for (usize i = src_len; i > 0; --i) {
        if (is_separator(src[i - 1])) {
            len = i;
            break;
        }
    }

    if (dst != NULL && dst_size > 0) {
        usize n = len < dst_size ? len : dst_size - 1;
        cspd_memcpy(dst, src, n);
        dst[n] = '\0';
    }

    return len;
}
