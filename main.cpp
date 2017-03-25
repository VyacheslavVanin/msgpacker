#include <stdio.h>
#include "baseencode.h"
#include <string.h>
#include <arpa/inet.h>
#include "vvvtest.h"


int is_bit_set8(uint8_t value, uint32_t bit);
int is_bit_set16(uint16_t value, uint32_t bit);
int is_bit_set32(uint32_t value, uint32_t bit);


#define __is_bit_setN(bits) \
int is_bit_set##bits(uint##bits##_t value, uint32_t bit) \
{ \
    return ((1 << bit) & value) != 0; \
}

#define __high_maskN(bits) \
uint32_t high_mask##bits(uint32_t numbits) \
{ \
    return numbits ? UINT##bits##_MAX << ((bits) - numbits) \
                   : 0; \
}

#define __low_maskN(bits) \
uint##bits##_t low_mask##bits(uint32_t numbits) \
{ \
    return numbits ? UINT##bits##_MAX >> ((bits) - numbits) \
                   : 0; \
}

#define __mid_maskN(bits) \
uint##bits##_t mid_mask##bits(uint32_t offset, uint32_t width) \
{ \
    return width ? (UINT##bits##_MAX >> ((bits) - width))<< offset \
                 : 0; \
}

// https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
// a^((a^b)&mask) = (a & ~mask) | (b & mask) 
#define __set_mid_bitsN(bits) \
uint##bits##_t set_mid_bits##bits(uint##bits##_t in, \
                        uint32_t offset, uint32_t width, \
                        uint##bits##_t value) \
{ \
    const uint##bits##_t mask        = mid_mask##bits(offset, width); \
    const uint##bits##_t shifted_val = value << offset; \
    return in ^((in^shifted_val)&mask); \
}

#define __get_mid_bitsN(bits) \
uint##bits##_t get_mid_bits##bits(uint##bits##_t in, \
                                  uint32_t offset, uint32_t width) \
{ \
    return (in << ((bits) - (offset + width))) >> ((bits) - width); \
}

#define define_for_all_bitsizes(d) \
    d(8); \
    d(16); \
    d(32); \
    d(64);

define_for_all_bitsizes(__is_bit_setN)
define_for_all_bitsizes(__high_maskN)
define_for_all_bitsizes(__low_maskN)
define_for_all_bitsizes(__mid_maskN)
define_for_all_bitsizes(__set_mid_bitsN)
define_for_all_bitsizes(__get_mid_bitsN)



void print_bits(uint8_t value)
{
    for(size_t i = 0; i < 8; ++i)
        printf("%d", is_bit_set8(value, 7-i));
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

typedef struct foo
{
    uint32_t b:1;
    uint32_t f:16;
    uint32_t d:15;
}foo;




VVVTEST_EQ(test_highmask4, high_mask32(4) == 0xf0000000)
VVVTEST_EQ(test_highmask8, high_mask32(8) == 0xff000000)
VVVTEST_EQ(test_highmask12, high_mask32(12) == 0xfff00000)
VVVTEST_EQ(test_highmask13, high_mask32(13) == 0xfff80000)
VVVTEST_EQ(test_lowmask4, low_mask32(4) == 0x0000000f)
VVVTEST_EQ(test_lowmask8, low_mask32(8) == 0x000000ff)
VVVTEST_EQ(test_lowmask13, low_mask32(13) == 0x00001fff)

VVVTEST_EQ(test_midmask1, mid_mask32(0, 8) == 0x000000ff)
VVVTEST_EQ(test_midmask2, mid_mask32(4, 8) == 0x00000ff0)

VVVTEST_EQ(test_isbitset1, is_bit_set8(0x04, 0) == false)
VVVTEST_EQ(test_isbitset2, is_bit_set8(0x01, 0) == true)
VVVTEST_EQ(test_isbitset3, is_bit_set8(0x04, 1) == false)
VVVTEST_EQ(test_isbitset4, is_bit_set8(0x02, 1) == true)
VVVTEST_EQ(test_isbitset5, is_bit_set8(0x04, 2) == true)
VVVTEST_EQ(test_isbitset6, is_bit_set8(0x04, 3) == false)

VVVTEST_EQ(test_set_mid_bits1, set_mid_bits32(0x12345678, 4, 16, 0xabcd) == 0x123abcd8)
VVVTEST_EQ(test_set_mid_bits2, set_mid_bits32(0x12345678, 0, 16, 0xabcd) == 0x1234abcd)
VVVTEST_EQ(test_set_mid_bits3, set_mid_bits32(0x12345678, 8, 16, 0xabcd) == 0x12abcd78)
VVVTEST_EQ(test_set_mid_bits4, set_mid_bits32(0x12345678, 12, 16, 0xabcd) == 0x1abcd678)
VVVTEST_EQ(test_set_mid_bits5, set_mid_bits32(0x12345678, 16, 16, 0xabcd) == 0xabcd5678)
VVVTEST_EQ(test_set_mid_bits6, set_mid_bits32(0x12345678, 20, 16, 0xabcd) == 0xbcd45678)

VVVTEST_EQ(test_get_mid_bits0, get_mid_bits32(0x12345678, 0,  8) == 0x78)
VVVTEST_EQ(test_get_mid_bits1, get_mid_bits32(0x12345678, 0, 16) == 0x5678)
VVVTEST_EQ(test_get_mid_bits2, get_mid_bits32(0x12345678, 4,  8) == 0x67)
VVVTEST_EQ(test_get_mid_bits3, get_mid_bits32(0x12345678, 28, 4) == 0x1)
VVVTEST_EQ(test_get_mid_bits4, get_mid_bits32(0x12345678, 24, 8) == 0x12)

int main()
{
    testall();
    
    uint32_t t1 = mid_mask32(1,16);
    uint32_t t1be = htonl(t1);
    print_bits32(t1);
    print_bits32(htobe32(t1));
    print_bits32(t1be);

    write_bits32(&t1be, 7, 5, 31);
    print_bits32(t1be);
    printf("%u\n", read_bits32(&t1be, 7, 5));

    foo f;
    f.b = 0;
    f.d = 0;
    f.f = 0xffff;
    print_bytes_bits(&f, 4);


    return 0;
}
