#ifndef BASEENCODE_H
#define BASEENCODE_H
#include <stdlib.h>
#include <stdint.h>

/*
 *  // Example:
 *  struct foo{
 *      uint16_t s;
 *      double   d;
 *      uint32_t l;
 *  };
 *
 *  struct bar {
 *      uint16_t s;
 *      foo      f;
 *  };
 *
 *  void* encode_foo(const foo* f, void* dst)
 *  {
 *      dst = encode_16(&f->s, dst);
 *      dst = encode_64(&f->d, dst);
 *      dst = encode_32(&f->l, dst);
 *      return dst;
 *  }
 *
 *  const void* decode_foo(const void* src, foo* f)
 *  {
 *      src = decode_16(src, &f->s);
 *      src = decode_64(src, &f->d);
 *      src = decode_32(src, &f->l);
 *      return src;
 *  }
 *  
 *  void* encode_bar(const bar* b, void* dst)
 *  {
 *      dst = encode_16(&b->s, dst);
 *      dst = encode_foo(&b->f, dst);
 *      return dst;
 *  }
 *
 *  const void* decode_bar(const void* src, bar* b)
 *  {
 *      src = decode_16(src, &b->s);
 *      src = decode_foo(src, &b->f);
 *      return src;
 *  }
 */


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Encode 1 byte from source and put to dest.
 * @param src pointer to value need to encode.
 * @param dest where to place encoded value.
 * @return next destination pos (dest+1) */
void* encode_8(const void* src, void* dest);

/**
 * @brief Encode 2 bytes from source and put to dest.
 * @param src pointer to value need to encode.
 * @param dest where to place encoded value.
 * @return next destination pos (dest+2) */
void* encode_16(const void* src, void* dest);

/**
 * @brief Encode 4 bytes from source and put to dest.
 * @param src pointer to value need to encode.
 * @param dest where to place encoded value.
 * @return next destination pos (dest+4) */
void* encode_32(const void* src, void* dest);

/**
 * @brief Encode 8 bytes from source and put to dest.
 * @param src pointer to value need to encode.
 * @param dest where to place encoded value.
 * @return next destination pos (dest+8) */
void* encode_64(const void* src, void* dest);

/**
 * @brief Decode 1 byte from source and put to dest.
 * @param src pointer to encoded value/
 * @param dest pointer to place decoded value.
 * @return  next source pos (src+1) */
const void* decode_8(const void* src, void* dest);

/**
 * @brief Decode 2 bytes from source and put to dest.
 * @param src pointer to encoded value/
 * @param dest pointer to place decoded value.
 * @return  next source pos (src+2) */
const void* decode_16(const void* src, void* dest);

/**
 * @brief Decode 4 bytes from source and put to dest.
 * @param src pointer to encoded value/
 * @param dest pointer to place decoded value.
 * @return  next source pos (src+4) */
const void* decode_32(const void* src, void* dest);

/**
 * @brief Decode 8 bytes from source and put to dest.
 * @param src pointer to encoded value/
 * @param dest pointer to place decoded value.
 * @return  next source pos (src+8) */
const void* decode_64(const void* src, void* dest);

char* cencode_8(const void* src, char* dst);
char* cencode_16(const void* src, char* dst);
char* cencode_32(const void* src, char* dst);
char* cencode_64(const void* src, char* dst);

const char* cdecode_8(const char* src, void* dst);
const char* cdecode_16(const char* src, void* dst);
const char* cdecode_32(const char* src, void* dst);
const char* cdecode_64(const char* src, void* dst);

#ifdef __cplusplus
}
#endif

#endif
