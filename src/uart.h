
#ifndef _UART_H
#define _UART_H



#define UART0_BASE 0x3F000000

#define AUX_ENBL *(volatile unsigned int *)(UART0_BASE + 0x215004)
#define AUX_MU_IO_REG *(volatile unsigned int *)(UART0_BASE + 0x215040)
#define AUX_MU_LCR_REG *(volatile unsigned int* ) (UART0_BASE + 0x21504C)
#define AUX_MU_LSR_REG *(volatile unsigned int* ) (UART0_BASE + 0x215054)
#define AUX_MU_CNTL_REG *(volatile unsigned int*) (UART0_BASE + 0x215060)
#define AUX_MU_BAUD_REG *(volatile unsigned int*) (UART0_BASE + 0x215068)

// GPIO регистры для конфигурации пинов TXD/RXD
#define GPIO_BASE 0x3F200000
#define GPFSEL1 *(volatile unsigned int *)(GPIO_BASE + 0x04)
#define GPPUD *(volatile unsigned int *)(GPIO_BASE + 0x94)
#define GPPUDCLK0 *(volatile unsigned int *)(GPIO_BASE + 0x98)

void UART_Init ();

#endif // _dUART_H