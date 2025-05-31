#ifdef __WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif
#include "baseencode.h"
#include <string.h>

#if !defined(HOST_ENDIANESS_LITTLE) && !defined(HOST_ENDIANESS_BIG)
    #if defined(__sparc__) || defined(__sparc_v8__) || defined(__sparc_v9__)
        #define HOST_ENDIANESS_BIG
    #else
        #define HOST_ENDIANESS_LITTLE
    #endif
#endif

static uint64_t swap_bytes(uint64_t src)
{
    uint8_t  t; 
    uint8_t* p = (uint8_t*)&src;
    t = p[0]; p[0] = p[7]; p[7] = t;
    t = p[1]; p[1] = p[6]; p[6] = t;
    t = p[2]; p[2] = p[5]; p[5] = t;
    t = p[3]; p[3] = p[4]; p[4] = t;
    return src;
}

static uint64_t ntohll(uint64_t src)
{
#ifdef HOST_ENDIANESS_BIG
    return src;
#else
    return swap_bytes(src);
#endif
}

static uint64_t htonll(uint64_t src)
{
#ifdef HOST_ENDIANESS_BIG
    return src;
#else
    return swap_bytes(src);
#endif
}


static uint16_t ntoh16_p(const void* src)
{
    uint16_t tmp;
    memcpy(&tmp,src,sizeof(tmp));
    return ntohs(tmp);
}

static uint32_t ntoh32_p(const void* p)
{
    uint32_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return ntohl(tmp);
}

static uint64_t ntoh64_p(const void* p)
{
    uint64_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return ntohll(tmp);
}

static uint16_t hton16_p(const void* p)
{
    uint16_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return htons(tmp);
}

static uint32_t hton32_p(const void* p)
{
    uint32_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return htonl(tmp);
}

static uint64_t hton64_p(const void* p)
{
    uint64_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return htonll(tmp);
}


void* encode_8(const void* src, void* dest)
{
     *(uint8_t*)dest = *(uint8_t*)src;
     return (uint8_t*)dest+1;
}

void* encode_16(const void* src, void* dest)
{
    const uint16_t n = hton16_p(src);
    memcpy(dest, &n, sizeof(n));
    return (uint8_t*)dest + sizeof(n);
}


void* encode_32(const void* src, void* dest)
{
    const uint32_t n = hton32_p(src);
    memcpy(dest, &n, sizeof(n));
    return (uint8_t*)dest + sizeof(n);
}


void* encode_64(const void* src, void* dest)
{
    const uint64_t n = hton64_p(src);
    memcpy(dest, &n, sizeof(n));
    return (uint8_t*)dest + sizeof(n);
}


const void* decode_8(const void* src, void* dest)
{
     *(uint8_t*)dest = *(uint8_t*)src;
     return (uint8_t*)src + 1;
}


const void* decode_16(const void* src, void* dest)
{
    const uint16_t n = ntoh16_p(src);
    memcpy(dest, &n, sizeof(n));
    return (uint8_t*)src + sizeof(n);
}


const void* decode_32(const void* src, void* dest)
{
    const uint32_t n = ntoh32_p(src);
    memcpy(dest, &n, sizeof(n));
    return (uint8_t*)src + sizeof(n);
}


const void* decode_64(const void* src, void* dest)
{
    const uint64_t n = ntoh64_p(src);
    memcpy(dest, &n, sizeof(n));
    return (uint8_t*)src + sizeof(n);
}

char* cencode_8(const void* src, char* dst)
{
    return (char*)encode_8(src, dst);
}
char* cencode_16(const void* src, char* dst)
{
    return (char*)encode_16(src, dst);
}
char* cencode_32(const void* src, char* dst)
{
    return (char*)encode_32(src, dst);
}
char* cencode_64(const void* src, char* dst)
{
    return (char*)encode_64(src, dst);
}

const char* cdecode_8(const char* src, void* dst)
{
    return (char*)decode_8(src, dst);
}
const char* cdecode_16(const char* src, void* dst)
{
    return (char*)decode_16(src, dst);
}
const char* cdecode_32(const char* src, void* dst)
{
    return (char*)decode_32(src, dst);
}
const char* cdecode_64(const char* src, void* dst)
{
    return (char*)decode_64(src, dst);
}
