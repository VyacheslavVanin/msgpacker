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

uint32_t ptou32(const void* ptr)
{
    uint32_t ret;
    for(size_t i = 0; i < 4; ++i)
        ((uint8_t*)&ret)[i] = ((uint8_t*)ptr)[i];
    return ret;
}

void u32top(void* ptr, uint32_t val)
{
    for(size_t i = 0; i < 4; ++i)
        ((uint8_t*)ptr)[i] = ((uint8_t*)&val)[i];
}

void write_bits32(void* ptr, uint32_t bits_offset, uint32_t width,
                  uint32_t value)
{
    const uint32_t a = ntohl(ptou32(ptr)); // load as uint32
    const uint32_t result = htonl(set_mid_bits32(a, bits_offset, width, value));
    u32top(ptr, result); // store as uint32
}

uint32_t read_bits32(void* ptr, uint32_t offset, uint32_t width)
{
    const uint32_t ret = ntohl(ptou32(ptr));
    return get_mid_bits32(ret, offset, width);
}


