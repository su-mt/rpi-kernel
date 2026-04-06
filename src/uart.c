#include "uart.h"

static inline void delay(int count) {
    while(count--) {
        // nop (No Operation) не дает компилятору вырезать этот цикл при оптимизации
        __asm__ __volatile__("nop"); 
    }

}



void UART_Init () {
    // Зафиксировать GPIO14 и GPIO15 в ALT5 для mini UART TXD/RXD
    // GPFSEL1: биты 12-14 для GPIO14 (ALT5=010), биты 15-17 для GPIO15 (ALT5=010)
    GPFSEL1 &= ~((7 << 12) | (7 << 15)); // Очищаем биты
    GPFSEL1 |= ((2 << 12) | (2 << 15));  // Устанавливаем ALT5 (010b)

    // Отключаем pull-ups/downs для GPIO14 и GPIO15
    GPPUD = 0;      // Отключаем pull-up/down
    delay(150);     // Задержка
    GPPUDCLK0 = (1 << 14) | (1 << 15); // Применяем к GPIO14 и GPIO15
    delay(150);     // Задержка
    GPPUDCLK0 = 0;  // Отключаем часы

    // Инициализация mini UART
    AUX_ENBL = 0;
    AUX_ENBL |= (1 << 0); // Включаем UART0

    AUX_MU_LCR_REG = 3; // Сброс всех битов в регистре Line Control
    AUX_MU_BAUD_REG = 271;

    // Включаем TX и RX в регистре CNTL: бит 0 RX enable, бит 1 TX enable
    AUX_MU_CNTL_REG = 3;

    // Основной цикл: отправляем 'A' каждые ~1М тактов
    for(;;) {
        // Ждем, пока 5-й бит (TX empty) в регистре LSR станет равен 1
        while (!(AUX_MU_LSR_REG & (1 << 5))); 
        
        // Прямая запись символа
        AUX_MU_IO_REG = 'A'; 
        
        delay(1000000);
    }
}