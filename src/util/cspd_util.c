#define CSPD_EXPORTS

#include "cspd_util.h"
#include "cspd_types.h"
#include <stdio.h>

void cspd_swap(void *pa, void *pb, size_t size)
{
    u8  tmp;
    u8 *a = pa, *b = pb;

    while (size--) {
        tmp  = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}

void cspd_print_binary(void *data, size_t size)
{
    // https://code-vault.net/lesson/0iqp12va9m:1603820088926
    for (u64 i = 0; i < size; i++) {
        u8 byte = ((i8 *)data)[i];
        for (u64 j = sizeof(u64); j > 0; j--) {
            u8 bit = (byte >> j) & 1;
            printf("%hhd", bit);
        }
        printf(" ");
    }
}
