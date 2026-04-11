#include "uart.h"
#include "printf.h"
#include "memory_map/memory.h"
#include <stdint.h>



// Базовый адрес GPIO для RPi Zero 2 W
#define GPIO_BASE 0x3F200000

// Определяем указатели на регистры в памяти
#define GPFSEL2 *(volatile unsigned int *)(GPIO_BASE + 0x08)
#define GPSET0  *(volatile unsigned int *)(GPIO_BASE + 0x1C)
#define GPCLR0  *(volatile unsigned int *)(GPIO_BASE + 0x28)

const char* global_str = "hello";

static void delay(int count) {
    while(count--) {
        asm volatile("nop"); 
    }

}

void print_hi_from_vs () {
    
    printf_("hi\n");
}


void kernel_main(){
    asm volatile(
    "dsb\n"          // Data Synchronization Barrier
    "isb\n"          // Instruction Synchronization Barrier
    "mcr p15, 0, r0, c8, c7, 0\n" // Invalidate TLB
    "mcr p15, 0, r0, c7, c5, 0\n" // Invalidate Instruction Cache
    ::: "r0", "memory"
    );  
    int* i_ptr;
    int i32 = 100;
    i_ptr = &i32;
    
    void (*virtual)(void) = (void (*)(void))((uintptr_t)print_hi_from_vs + 0x80000000);
    print_hi_from_vs();
    printf_("ptr is %p, func is %p\n",virtual, print_hi_from_vs);
    virtual();

    for (;;){
        printf("Hi from virtual space\n");

        printf("string %s placed at addr %p\n", global_str, &global_str);
        printf("digit %d placed at addr %p\n", i32, i_ptr);
        
        printf_("addr of kernel_main id %p", &kernel_main);
        
        delay(10000000);

    }
}

void main() {
    printf("string %s placed at addr %p\n", global_str, &global_str);
    UART_puts("M0\n");
    printf("start\n");
    UART_puts("M1\n");
    init_MAIR();
    UART_puts("M2\n");
    init_kernel_l2_pages();
    UART_puts("M3\n");

    // С ORIGIN=PHYS_RAM_BASE все адреса уже физические
    init_kernel_l1_page(&l1[0], l2);
    init_kernel_l1_page(&l1[2], l2);
    UART_puts("M4\n");

    asm volatile("dsb");

    uint64_t l1_phys   = (uintptr_t)&l1[0];     
    uint32_t jump_addr = (uint32_t)kernel_main;
    UART_puts("M5\n");
    init_mmu(l1_phys, jump_addr);
    UART_puts("MX\n");

    
}

void led_blink() {

    GPFSEL2 &= ~(7 << 27); 
    // Записываем 001 в биты 3-5
    GPFSEL2 |= (1 << 27);  

    for(;;) {
        GPSET0 = (1 << 29); 
        delay(900000);
        GPCLR0 = (1 << 29);  // Выключить ток на GPIO 21
        delay(900000);
        
    }
}
