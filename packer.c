#include "packer.h"
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>

#if defined(__sparc__) || defined(__v8__) || defined(__v9__)
#define HOST_ENDIANESS_BIG
#else
#define HOST_ENDIANESS_LITTLE
#endif


static uint64_t ntohll(uint64_t src)
{
#ifdef HOST_ENDIANESS_BIG
    return src;
#else
    uint8_t  t; 
    uint8_t* p = (uint8_t*)&src;
    t = p[0]; p[0] = p[7]; p[7] = t;
    t = p[1]; p[1] = p[6]; p[6] = t;
    t = p[2]; p[2] = p[5]; p[5] = t;
    t = p[3]; p[3] = p[4]; p[4] = t;
    return src;
#endif
}

static uint64_t htonll(uint64_t src)
{
#ifdef HOST_ENDIANESS_BIG
    return src;
#else
    uint8_t  t; 
    uint8_t* p = (uint8_t*)&src;
    t = p[0]; p[0] = p[7]; p[7] = t;
    t = p[1]; p[1] = p[6]; p[6] = t;
    t = p[2]; p[2] = p[5]; p[5] = t;
    t = p[3]; p[3] = p[4]; p[4] = t;
    return src;
#endif
}


uint16_t ntoh16_p(const void* src)
{
    uint16_t tmp;
    memcpy(&tmp,src,sizeof(tmp));
    return ntohs(tmp);
}

uint32_t ntoh32_p(const void* p)
{
    uint32_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return ntohl(tmp);
}

uint64_t ntoh64_p(const void* p)
{
    uint64_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return ntohll(tmp);
}

uint16_t hton16_p(const void* p)
{
    uint16_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return htons(tmp);
}

uint32_t hton32_p(const void* p)
{
    uint32_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return htonl(tmp);
}

uint64_t hton64_p(const void* p)
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
