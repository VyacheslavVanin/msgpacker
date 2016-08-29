#ifndef BASEENCODE_H
#define BASEENCODE_H
#include <stdlib.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

void* encode_8(const void* src, void* dest);
void* encode_16(const void* src, void* dest);
void* encode_32(const void* src, void* dest);
void* encode_64(const void* src, void* dest);

const void* decode_8(const void* src, void* dest);
const void* decode_16(const void* src, void* dest);
const void* decode_32(const void* src, void* dest);
const void* decode_64(const void* src, void* dest);

#ifdef __cplusplus
}
#endif

#endif
