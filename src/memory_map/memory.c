#include "memory.h"
#include <stdbool.h>
#include <sys/cdefs.h>
#include <stddef.h>


void init_MAIR(void) {
    uint32_t mair0 = 0;
    
    // Слот 0: Device-nGnRnE (0x00)
    mair0 |= (0x00 << 0);
    // Слот 1: Normal Write-Back (0xFF)
    mair0 |= (0xFF << 8);
    // Слот 2: Normal Non-Cacheable (0x44)
    mair0 |= (0x44 << 16);

    // Записываем в системный регистр CP15
    asm volatile("mcr p15, 0, %0, c10, c2, 0" : : "r" (mair0));
}



bool set_bits(lpae_desc_t *desc, uint8_t start, uint8_t end, uint64_t bits) {
    if (desc == NULL || start > end || end >= 64) {
        return false;
    }

    uint8_t width = (uint8_t)(end - start + 1);
    uint64_t field_mask;
    uint64_t mask;

    if (width == 64) {
        field_mask = UINT64_MAX;
        mask = UINT64_MAX;
    } else {
        field_mask = (1ULL << width) - 1ULL;
        mask = field_mask << start;
    }

    *desc = (*desc & ~mask) | ((bits & field_mask) << start);
    return true;
}

uint64_t read_bits(uint8_t start, uint8_t end, lpae_desc_t desc) {
    if (start > end || end >= 64) {
        return 0;
    }

    uint8_t width = (uint8_t)(end - start + 1);
    uint64_t field_mask;

    if (width == 64) {
        field_mask = UINT64_MAX;
    } else {
        field_mask = (1ULL << width) - 1ULL;
    }

    return (desc >> start) & field_mask;
}



__attribute__((section("data.pgs")))
lpae_desc_t l1[4] = {0};

__attribute__((section("data.pgs")))
lpae_desc_t l2[512] = {0};

__attribute__((section("data.pgs")))
lpae_desc_t l3[512] = {0};


bool init_kernel_l1_page(lpae_desc_t* l1_page, const lpae_desc_t* next_lvl_pj) {


    set_bits(l1_page, 0, 1, 0b11);
    set_bits(l1_page, 12, 39, (uint64_t)next_lvl_pj);
    set_bits(l1_page, 40, 52, 0);
    set_bits(l1_page, 59, 63, 0); // rules for all kernel l2 pages; must be rwx

    return true;
}


bool create_l2_block(lpae_desc_t* l2_page ,uint64_t phys_addr, uint64_t ram_attrs) {

    set_bits(l2_page, 0, 1, 0b01);
    set_bits(l2_page, 2, 4, ram_attrs);
    set_bits(l2_page, 5, 5, 1);
    set_bits(l2_page, 6, 7, 0b00);
    set_bits(l2_page, 8, 9, 0b00);
    set_bits(l2_page, 10, 10, 1);
    set_bits(l2_page, 21, 39, phys_addr);

    return true;
}

void init_kernel_l2_pages(void) {
    for (int i = 0; i < 64; i++) {
        uint64_t phys_addr = i * 0x200000; // Шаг 2 МБ
        create_l2_block(&l2[i], phys_addr, 0); 
    }
}

