#include "baseencode.h"
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "bitops.h"
#include "vvvtest.h"

VVVTEST_EQ(high_mask32(4) == 0xf0000000)
VVVTEST_EQ(high_mask32(8) == 0xff000000)
VVVTEST_EQ(high_mask32(12) == 0xfff00000)
VVVTEST_EQ(high_mask32(13) == 0xfff80000)
VVVTEST_EQ(low_mask32(4) == 0x0000000f)
VVVTEST_EQ(low_mask32(8) == 0x000000ff)
VVVTEST_EQ(low_mask32(13) == 0x00001fff)

VVVTEST_EQ(mid_mask32(0, 8) == 0x000000ff)
VVVTEST_EQ(mid_mask32(4, 8) == 0x00000ff0)

VVVTEST_EQ(is_bit_set8(0x04, 0) == false)
VVVTEST_EQ(is_bit_set8(0x01, 0) == true)
VVVTEST_EQ(is_bit_set8(0x04, 1) == false)
VVVTEST_EQ(is_bit_set8(0x02, 1) == true)
VVVTEST_EQ(is_bit_set8(0x04, 2) == true)
VVVTEST_EQ(is_bit_set8(0x04, 3) == false)

VVVTEST_EQ(set_bits32(0x12345678, 4, 16, 0xabcd) == 0x123abcd8)
VVVTEST_EQ(set_bits32(0x12345678, 0, 16, 0xabcd) == 0x1234abcd)
VVVTEST_EQ(set_bits32(0x12345678, 8, 16, 0xabcd) == 0x12abcd78)
VVVTEST_EQ(set_bits32(0x12345678, 12, 16, 0xabcd) == 0x1abcd678)
VVVTEST_EQ(set_bits32(0x12345678, 16, 16, 0xabcd) == 0xabcd5678)
VVVTEST_EQ(set_bits32(0x12345678, 20, 16, 0xabcd) == 0xbcd45678)

VVVTEST_EQ(get_bits32(0x12345678, 0,  8) == 0x78)
VVVTEST_EQ(get_bits32(0x12345678, 0, 16) == 0x5678)
VVVTEST_EQ(get_bits32(0x12345678, 4,  8) == 0x67)
VVVTEST_EQ(get_bits32(0x12345678, 28, 4) == 0x1)
VVVTEST_EQ(get_bits32(0x12345678, 24, 8) == 0x12)

VVVTEST_EQ(get_bits8(0xa8, 0, 4) == 0x8)
VVVTEST_EQ(get_bits8(0xa8, 4, 4) == 0xa)
VVVTEST_EQ(get_bits32(0x12345678, 0,  4) == 0x8)
VVVTEST_EQ(get_bits32(0x12345678, 24,  8) == 0x12)
VVVTEST_EQ(get_bits32(0x26a0b8d7, 24, 8) == 0x26)
VVVTEST_EQ(is_bit_set64(0x00000000ffffffffUll, 0) == 1)
VVVTEST_EQ(is_bit_set64(0x00000000ffffffffUll, 63) == 0)
VVVTEST_EQ(is_bit_set64(0xffffffff00000000Ull, 63) == 1)

int main()
{
    testall();

    return 0;
}
