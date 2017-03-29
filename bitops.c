#include "bitops.h"
#include <stdio.h>
#if defined __linux__
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif

void print_bytes_bits(const void* src, uint32_t numbytes)
{
    const uint8_t* bytes = (const uint8_t*)src;
    for(uint32_t i = 0; i < numbytes; ++i) {
        print_bits8(bytes[i]);
        printf(" ");
    }
    printf("\n");
}

void print_bits8(uint8_t value)
{
    for(uint32_t i = 0; i < 8; ++i)
        printf("%d", is_bit_set8(value, 7-i));
}
void print_bits16(uint16_t value)
{
    print_bytes_bits(&value, 2);
}

void print_bits32(uint32_t value)
{
    print_bytes_bits(&value, 4);
}

void print_bits64(uint32_t value)
{
    print_bytes_bits(&value, 8);
}


