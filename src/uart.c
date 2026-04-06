#include "uart.h"


void UART_puts(const char* str) {
    while(*str !='\0'){
        UART_putchar(*str++);
    }
}

void UART_Init () {
    // Зафиксировать GPIO14 и GPIO15 в ALT5 для mini UART TXD/RXD
    // GPFSEL1: биты 12-14 для GPIO14 (ALT5=010), биты 15-17 для GPIO15 (ALT5=010)
    GPFSEL1 &= ~((7 << 12) | (7 << 15)); // Очищаем биты
    GPFSEL1 |= ((2 << 12) | (2 << 15));  // Устанавливаем ALT5 (010b)

    // Отключаем pull-ups/downs для GPIO14 и GPIO15
    GPPUD = 0;      // Отключаем pull-up/down
    GPPUDCLK0 = (1 << 14) | (1 << 15); // Применяем к GPIO14 и GPIO15
    GPPUDCLK0 = 0;  // Отключаем часы

    // Инициализация mini UART
    AUX_ENBL = 0;
    AUX_ENBL |= (1 << 0); // Включаем UART0

    AUX_MU_LCR_REG = 3; // Сброс всех битов в регистре Line Control
    AUX_MU_BAUD_REG = 271;

    // Включаем TX и RX в регистре CNTL: бит 0 RX enable, бит 1 TX enable
    AUX_MU_CNTL_REG = 3;


}