#define LIBCSPD_EXPORTS

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

void print_binary(void *data, size_t size)
{
    // https://code-vault.net/lesson/0iqp12va9m:1603820088926
    for (uint64 i = 0; i < size; i++) {
        uint8 byte = ((int8 *)data)[i];
        for (uint64 j = sizeof(uint64); j > 0; j--) {
            uint8 bit = (byte >> j) & 1;
            printf("%hhd", bit);
        }
        printf(" ");
    }
}
