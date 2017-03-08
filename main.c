#include <stdio.h>
#include "baseencode.h"
#include <string.h>
#include <arpa/inet.h>

int is_bit_set(uint8_t value, uint8_t bit)
{
    return ((1 << bit) & value) != 0;
}

void print_bits(uint8_t value)
{
    for(size_t i = 0; i < 8; ++i)
        printf("%d", is_bit_set(value, 7-i));
}

void print_bytes_bits(const void* src, size_t numbytes)
{
    const uint8_t* bytes = (const uint8_t*)src;
    for(size_t i = 0; i < numbytes; ++i) {
        print_bits(bytes[i]);
        printf(" ");
    }
    printf("\n");
}

void print_bits8(uint8_t value)
{
    print_bytes_bits(&value, 1);
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

uint32_t high_mask32(uint32_t numbits)
{
    return numbits ? UINT32_MAX << (32 - numbits)
                   : 0;
}

uint32_t low_mask32(uint32_t numbits)
{
    return numbits ? UINT32_MAX >> (32 - numbits)
                   : 0;
}

uint32_t mid_mask32(uint32_t offset, uint32_t width)
{
    return width ? (UINT32_MAX >> (32 - width))<< offset
                 : 0;
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


void write_bits32(void* ptr, uint32_t value,
                  uint32_t bits_offset, uint32_t width)
{
    const uint32_t mask        = mid_mask32(bits_offset, width); // 0.0f.f0.0
    const uint32_t shifted_val = value << bits_offset;

    uint32_t a = ntohl(ptou32(ptr)); // load as uint32
    // https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
    // a^((a^b)&mask) = (a & ~mask) | (b & mask)
    const uint32_t result = htonl(a ^((a^shifted_val)&mask));
    u32top(ptr, result); // store as uint32
}

uint32_t read_bits32(void* ptr, uint32_t offset, uint32_t width)
{
    uint32_t ret = ntohl(ptou32(ptr));
    ret = (ret << (32 - (offset + width))) >> (32 - width);
    return ret;
}

typedef struct foo
{
    uint32_t b:1;
    uint32_t f:16;
    uint32_t d:15;
}foo;


int main()
{
    uint32_t res = 0x11223344;
    printf("%0x\n", res);
    res &= high_mask32(8) | low_mask32(4);
    printf("%0x\n", res);

    uint32_t test = 0xff22ffaa;
    print_bytes_bits(&test, 4);

    print_bits32(high_mask32(4) | low_mask32(4));

    print_bits32(mid_mask32(0,2));
    print_bits32(~mid_mask32(0,2));


    uint32_t t1 = mid_mask32(1,16);
    uint32_t t1be = htonl(t1);
    print_bits32(t1);
    print_bits32(htobe32(t1));
    print_bits32(t1be);

    write_bits32(&t1be, 31, 7, 5);
    print_bits32(t1be);
    printf("%u\n", read_bits32(&t1be, 7, 5));

    foo f;
    f.b = 0;
    f.d = 0;
    f.f = 0xffff;
    print_bytes_bits(&f, 4);

    return 0;
}
