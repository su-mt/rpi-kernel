#include "memory.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/cdefs.h>
#include <stddef.h>
#include "../uart.h"


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

void init_mmu(uint64_t l1_phys_addr, uint32_t jump_addr) {
    UART_puts("T0\n");
    uint32_t ttbcr = (1u << 31);
    asm volatile("mcr p15, 0, %0, c2, c0, 2" : : "r" (ttbcr));
    asm volatile("isb");   
    UART_puts("T1\n");

    uint32_t low  = (uint32_t)l1_phys_addr;
    uint32_t high = (uint32_t)(l1_phys_addr >> 32);
    asm volatile("mcrr p15, 0, %0, %1, c2" : : "r" (low), "r" (high));
    asm volatile("isb");   
    UART_puts("T2\n");
    
    asm volatile (
        "mov r2, #0\n"
        "mcr p15, 0, r2, c8, c7, 0\n"
        "dsb\n"
        "isb\n"
        "mrc p15, 0, r2, c1, c0, 0\n"
        "orr r2, r2, #0x1\n"
        "mcr p15, 0, r2, c1, c0, 0\n"
        "dsb\n"
        "isb\n"
        "mov pc, %0\n"
        : : "r" (jump_addr) : "r2", "memory"
    );

    UART_puts("TX\n");
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



__attribute__((section(".l1_table"), aligned(4096)))
lpae_desc_t l1[4];

__attribute__((section(".l2_table"), aligned(4096)))
lpae_desc_t l2[512];

__attribute__((section(".l3_table"), aligned(4096)))
lpae_desc_t l3[512];


bool init_kernel_l1_page(lpae_desc_t* l1_page, const lpae_desc_t* next_lvl_pj) {

    
    set_bits(l1_page, 0, 1, 0b11);
    set_bits(l1_page, 12, 39, (uint64_t)next_lvl_pj >> 12);
    set_bits(l1_page, 40, 52, 0);
    set_bits(l1_page, 59, 63, 0); // rules for all kernel l2 pages; must be rwx

    return true;
}


bool create_l2_block(lpae_desc_t* l2_page ,uint64_t phys_addr, uint64_t ram_attrs) {
    UART_puts("B0\n");
    set_bits(l2_page, 0, 64, 0);
    set_bits(l2_page, 0, 1, 0b01);
    set_bits(l2_page, 2, 4, ram_attrs);
    set_bits(l2_page, 5, 5, 1);
    set_bits(l2_page, 6, 7, 0b00);
    set_bits(l2_page, 8, 9, 0b11);
    set_bits(l2_page, 10, 10, 1);
    set_bits(l2_page, 21, 39, phys_addr);

    UART_puts("B1\n");

    return true;
}
void init_kernel_l2_pages(void) {
    UART_puts("L20\n");

    for (int i = 0; i < 64; i++) {
        if (i == 0) {
            UART_puts("L2A\n");
        }
        if (i == 32) {
            UART_puts("L2B\n");
        }
        if (i == 63) {
            UART_puts("L2C\n");
        }
        uint64_t phys_addr = i * 0x200000;
        create_l2_block(&l2[i], phys_addr >> 21, 1); 
    }
    UART_puts("L2D\n");
    create_l2_block(&l2[505], 0x3F200000 >> 21, 0); // Атрибут 0 - Device Memory
    UART_puts("L2E\n");
}




