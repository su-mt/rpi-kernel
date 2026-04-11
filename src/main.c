#include "uart.h"
#include "printf.h"
#include "memory_map/memory.h"



// Базовый адрес GPIO для RPi Zero 2 W
#define GPIO_BASE 0x3F200000

// Определяем указатели на регистры в памяти
#define GPFSEL2 *(volatile unsigned int *)(GPIO_BASE + 0x08)
#define GPSET0  *(volatile unsigned int *)(GPIO_BASE + 0x1C)
#define GPCLR0  *(volatile unsigned int *)(GPIO_BASE + 0x28)


static void delay(int count) {
    while(count--) {
        asm volatile("nop"); 
    }

}


void main() {
    printf("start\n");
    init_kernel_l2_pages();
    init_kernel_l1_page(&l1[2], l2);
    
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
