// Базовый адрес GPIO для RPi Zero 2 W
#define GPIO_BASE 0x3F200000

// Определяем указатели на регистры в памяти
#define GPFSEL2 *(volatile unsigned int *)(GPIO_BASE + 0x08)
#define GPSET0  *(volatile unsigned int *)(GPIO_BASE + 0x1C)
#define GPCLR0  *(volatile unsigned int *)(GPIO_BASE + 0x28)


extern void main();
void _Exit(int exit_code) __attribute__((noreturn, noinline));


__attribute__((naked, section(".text._enter")))
void _enter(void) {
    asm volatile (
        "mrc p15, 0, r0, c0, c0, 5\n"
        "ands r0, r0, #3\n"
        "beq  .core0\n"       
        "b .halt\n"

        ".core0:\n"
        "   mov sp, #0x800000\n"
        "   ldr r1, =0x4000009C\n"
        "   ldr r2, =core1_init\n"
        "   str r2, [r1]\n"
        "   dsb\n"
        "   sev\n"
        "   bl main\n"
        "   b .halt\n"
    
        ".halt: \n"
        "   wfe\n"
        "   b .halt\n"
    );
}


void delay(int count) {
    while(count--) {
        asm volatile("nop"); 
    }

}

__attribute__((naked))
void core1_init() {
    asm volatile (
        "mov sp, #0x400000\n"
        "bl led_blink\n"
        "b .halt\n"
    );
    
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


