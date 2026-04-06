#include "uart.h"
#include <stdio.h>
#include "printf.h"


static void delay(int count) {
    while(count--) {
        asm volatile("nop"); 
    }

}


const char str [] = "Hello from global const var";
int size = sizeof(str);

const char str2[] = "Hello from syscall!";
int size2 = sizeof(str2);

void main() {
    static char buff2[25] = "hello from stack";
    for (;;) {
        snprintf(buff2,sizeof(buff2), "str: %s, len: %d\n", str, size);
        UART_Init(); 
        UART_putchar('A'); // работает
        UART_puts("heloos");  // работает
        UART_puts(str); 
        UART_puts(buff2); 
        printf("str: %s, digit: %d\n", "Hello from syscall", 5);  // работает!
        delay(4000000);
    }

    
}