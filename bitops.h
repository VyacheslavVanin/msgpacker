#ifndef BITOPS_H
#define BITOPS_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __is_bit_setN(bits) \
inline int is_bit_set##bits(uint##bits##_t value, uint32_t bit) \
{ \
    return ((1 << bit) & value) != 0; \
}

#define __high_maskN(bits) \
inline uint32_t high_mask##bits(uint32_t numbits) \
{ \
    return numbits ? UINT##bits##_MAX << ((bits) - numbits) \
                   : 0; \
}

#define __low_maskN(bits) \
inline uint##bits##_t low_mask##bits(uint32_t numbits) \
{ \
    return numbits ? UINT##bits##_MAX >> ((bits) - numbits) \
                   : 0; \
}

#define __mid_maskN(bits) \
inline uint##bits##_t mid_mask##bits(uint32_t offset, uint32_t width) \
{ \
    return width ? (UINT##bits##_MAX >> ((bits) - width))<< offset \
                 : 0; \
}

// https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
// a^((a^b)&mask) = (a & ~mask) | (b & mask) 
#define __set_bitsN(bits) \
inline uint##bits##_t set_bits##bits(uint##bits##_t in, \
                        uint32_t offset, uint32_t width, \
                        uint##bits##_t value) \
{ \
    const uint##bits##_t mask        = mid_mask##bits(offset, width); \
    const uint##bits##_t shifted_val = value << offset; \
    return in ^((in^shifted_val)&mask); \
}

#define __get_bitsN(bits) \
inline uint##bits##_t get_bits##bits(uint##bits##_t in, \
                                  uint32_t offset, uint32_t width) \
{ \
    return (in << ((bits) - (offset + width))) >> ((bits) - width); \
}

#define __define_for_all_bitsizes(d) \
    d(8); \
    d(16); \
    d(32); \
    d(64);

__define_for_all_bitsizes(__is_bit_setN)
__define_for_all_bitsizes(__high_maskN)
__define_for_all_bitsizes(__low_maskN)
__define_for_all_bitsizes(__mid_maskN)
__define_for_all_bitsizes(__set_bitsN)
__define_for_all_bitsizes(__get_bitsN)

void print_bytes_bits(const void* src, uint32_t numbytes);
void print_bits8(uint8_t value);
void print_bits16(uint16_t value);
void print_bits32(uint32_t value);
void print_bits64(uint32_t value);


#ifdef __cplusplus
}
#endif

#endif

