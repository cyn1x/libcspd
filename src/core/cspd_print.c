#define CSPD_EXPORTS

#include "cspd_print.h"

void cspd_print_binary(void *data, usize size)
{
    for (usize i = 0; i < size; i++) {
        u8 byte = ((const u8 *)data)[i];
        for (int j = 7; j >= 0; j--) {
            putchar(((byte >> j) & 1) ? '1' : '0');
        }
        putchar(' ');
    }
}
