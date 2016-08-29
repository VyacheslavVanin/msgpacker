#ifndef PACKER_H
#define PACKER_H
#include <stdlib.h>
#include <stdint.h>

uint16_t ntoh16_p(void*);
uint32_t ntoh32_p(void*);
uint64_t ntoh64_p(void*);
uint16_t hton16_p(void*);
uint32_t hton32_p(void*);
uint64_t hton64_p(void*);

typedef struct packer_t
{
    uint8_t* base;
    size_t current_pos;
    size_t max_size;
}packer_t;

int packer_init(packer_t* packer, void* base, size_t max_size);
int packer_put8(packer_t* packer, uint8_t v);
int packer_put16(packer_t* packer, uint16_t v);
int packer_put32(packer_t* packer, uint32_t v);
int packer_put64(packer_t* packer, uint64_t v);

typedef struct unpacker_t
{
    uint8_t* base;
    size_t   current_pos;
    size_t   max_size;
}unpacker_t;

int unpacker_init(unpacker_t* p, void* base, size_t max_size);
int unpacker_get8(unpacker_t* p, uint8_t* out); 
int unpacker_get16(unpacker_t* p, uint16_t* out); 
int unpacker_get32(unpacker_t* p, uint32_t* out); 
int unpacker_get64(unpacker_t* p, uint64_t* out); 


#endif
