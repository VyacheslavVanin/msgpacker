#include <stdio.h>
#include "baseencode.h"
#include <string.h>
#include <arpa/inet.h>
#include "bitops.h"
#include "vvvtest.h"

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

VVVTEST_EQ(test_set_bits1, set_bits32(0x12345678, 4, 16, 0xabcd) == 0x123abcd8)
VVVTEST_EQ(test_set_bits2, set_bits32(0x12345678, 0, 16, 0xabcd) == 0x1234abcd)
VVVTEST_EQ(test_set_bits3, set_bits32(0x12345678, 8, 16, 0xabcd) == 0x12abcd78)
VVVTEST_EQ(test_set_bits4, set_bits32(0x12345678, 12, 16, 0xabcd) == 0x1abcd678)
VVVTEST_EQ(test_set_bits5, set_bits32(0x12345678, 16, 16, 0xabcd) == 0xabcd5678)
VVVTEST_EQ(test_set_bits6, set_bits32(0x12345678, 20, 16, 0xabcd) == 0xbcd45678)

VVVTEST_EQ(test_get_bits0, get_bits32(0x12345678, 0,  8) == 0x78)
VVVTEST_EQ(test_get_bits1, get_bits32(0x12345678, 0, 16) == 0x5678)
VVVTEST_EQ(test_get_bits2, get_bits32(0x12345678, 4,  8) == 0x67)
VVVTEST_EQ(test_get_bits3, get_bits32(0x12345678, 28, 4) == 0x1)
VVVTEST_EQ(test_get_bits4, get_bits32(0x12345678, 24, 8) == 0x12)

VVVTEST_EQ(test_get_bits8, get_bits8(0xa8, 0, 4) == 0x8)
VVVTEST_EQ(test_get_bits9, get_bits8(0xa8, 4, 4) == 0xa)
VVVTEST_EQ(test_get_bits10, get_bits32(0x12345678, 0,  4) == 0x8)
VVVTEST_EQ(test_get_bits11, get_bits32(0x12345678, 24,  8) == 0x12)
VVVTEST_EQ(test_get_bits12, get_bits32(0x26a0b8d7, 24, 8) == 0x26)
VVVTEST_EQ(test64_1, is_bit_set64(0x00000000ffffffffUll, 0) == 1)
VVVTEST_EQ(test64_2, is_bit_set64(0x00000000ffffffffUll, 63) == 0)
VVVTEST_EQ(test64_3, is_bit_set64(0xffffffff00000000Ull, 63) == 1)

int main()
{
    testall();

    return 0;
}
