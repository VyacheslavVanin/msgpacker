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


uint16_t ntoh16_p(void* p)
{
    uint16_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return ntohs(tmp);
}

uint32_t ntoh32_p(void* p)
{
    uint32_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return ntohl(tmp);
}
uint64_t ntoh64_p(void* p)
{
    uint64_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return ntohll(tmp);
}

uint16_t hton16_p(void* p)
{
    uint16_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return htons(tmp);
}
uint32_t hton32_p(void* p)
{
    uint32_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return htons(tmp);
}
uint64_t hton64_p(void* p)
{
    uint64_t tmp;
    memcpy(&tmp,p,sizeof(tmp));
    return htons(tmp);
}


int packer_init(packer_t* p, void* base, size_t max_size)
{
    p->base = (uint8_t*)base;
    p->current_pos = 0;
    p->max_size = max_size;
    return 0;
}

int packer_put8(packer_t* p, uint8_t v)
{
    const size_t valueSize = sizeof(v);
    const size_t current_pos = p->current_pos;
    const size_t newPos = p->current_pos + valueSize;
    if(newPos > p->max_size) return -1;
    memcpy(p->base+current_pos, &v, valueSize);
    p->current_pos = newPos;
    return 0;
}

int packer_put16(packer_t* p, uint16_t v)
{
    const size_t valueSize = sizeof(v);
    const size_t current_pos = p->current_pos;
    const size_t newPos = p->current_pos + valueSize;
    if(newPos > p->max_size) {
        return -1;
    }
    else{
        const uint16_t value = htons(v); 
        memcpy(p->base+current_pos, &value, valueSize);
        p->current_pos = newPos;
    }
    return 0;
}

int packer_put32(packer_t* p, uint32_t v)
{
    const size_t valueSize = sizeof(v);
    const size_t current_pos = p->current_pos;
    const size_t newPos = p->current_pos + valueSize;
    if(newPos > p->max_size) {
        return -1;
    }
    else{
        const uint32_t value = htonl(v); 
        memcpy(p->base+current_pos, &value, valueSize);
        p->current_pos = newPos;
    }
    return 0;
}
int packer_put64(packer_t* p, uint64_t v)
{
    const size_t valueSize = sizeof(v);
    const size_t current_pos = p->current_pos;
    const size_t newPos = p->current_pos + valueSize;
    if(newPos > p->max_size) {
        return -1;
    }
    else{
        const uint64_t value = htonll(v); 
        memcpy(p->base+current_pos, &value, valueSize);
        p->current_pos = newPos;
    }
    return 0;
}



int unpacker_init(unpacker_t* p, void* base, size_t max_size)
{
    p->base = (uint8_t*)base;
    p->current_pos = 0;
    p->max_size = max_size;
    return 0;
}

int unpacker_get8(unpacker_t* p, uint8_t* out)
{
    const size_t curpos = p->current_pos;
    const size_t newPos = curpos + 1;
    if(newPos > p->max_size) {
        assert(0 && "buffer overflow");
        return -1;
    }
    else{
        *out = p->base[curpos];
        p->current_pos = newPos;
        return 0;
    }
}

int unpacker_get16(unpacker_t* p, uint16_t* out)
{
    const size_t valueSize = 2;
    const size_t curpos = p->current_pos;
    const size_t newPos = curpos + valueSize;
    if(newPos > p->max_size) {
        assert(0 && "buffer overflow");
        return -1;
    }
    else{
        uint16_t tmp;
        memcpy(&tmp, &p->base[curpos], valueSize);
        *out = ntohs(tmp);
        p->current_pos = newPos;
        return 0;
    }
}

int unpacker_get32(unpacker_t* p, uint32_t* out)
{
    const size_t valueSize = 4;
    const size_t curpos = p->current_pos;
    const size_t newPos = curpos + valueSize;
    if(newPos > p->max_size) {
        assert(0 && "buffer overflow");
        return -1;
    }
    else{
        uint32_t tmp;
        memcpy(&tmp, &p->base[curpos], valueSize);
        *out = ntohl(tmp);
        p->current_pos = newPos;
        return 0;
    }
}

int unpacker_get64(unpacker_t* p, uint64_t* out)
{
    const size_t valueSize = 8;
    const size_t curpos = p->current_pos;
    const size_t newPos = curpos + valueSize;
    if(newPos > p->max_size) {
        assert(0 && "buffer overflow");
        return -1;
    }
    else{
        uint64_t tmp;
        memcpy(&tmp, &p->base[curpos], valueSize);
        *out = ntohll(tmp);
        p->current_pos = newPos;
        return 0;
    }
}
