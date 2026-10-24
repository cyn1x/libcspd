#define CSPD_EXPORTS

#include "cspd_util.h"
#include "cspd_types.h"

void cspd_swap(void *pa, void *pb, usize size)
{
    u8  tmp;
    u8 *a = pa, *b = pb;

    while (size--) {
        tmp  = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}
