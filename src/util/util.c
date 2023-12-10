#include "util.h"

void swap(void *pa, void *pb, size_t size)
{
    uint8  tmp;
    uint8 *a = pa, *b = pb;

    while (size--) {
        tmp  = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}
