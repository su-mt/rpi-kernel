#ifndef _MEMORY_MAP_MEMORY_H
#define _MEMORY_MAP_MEMORY_H

#include "stdint.h"
#include <stdbool.h>

enum MemoryTypes { 
    Device,
    Normal,
    Cacheable,
    NonCacheable
};


typedef uint64_t lpae_desc_t;
bool set_bits(lpae_desc_t *desc, uint8_t start, uint8_t end, uint64_t bits);
uint64_t read_bits(uint8_t start, uint8_t end, lpae_desc_t desc);


bool init_kernel_l1_page(lpae_desc_t* l1_page,const lpae_desc_t* next_lvl_pj) ;
void init_kernel_l2_pages(void);

extern lpae_desc_t l1[4];
extern lpae_desc_t l2[512];
extern lpae_desc_t l3[512];

#endif // _MEMORY_MAP_MEMORY_H