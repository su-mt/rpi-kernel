// Базовый адрес GPIO для RPi Zero 2 W
#define GPIO_BASE 0x3F200000

// Определяем указатели на регистры в памяти
#define GPFSEL2 *(volatile unsigned int *)(GPIO_BASE + 0x08)
#define GPSET0  *(volatile unsigned int *)(GPIO_BASE + 0x1C)
#define GPCLR0  *(volatile unsigned int *)(GPIO_BASE + 0x28)

__attribute__((naked, section(".text._enter")))
void _enter(void) {
    asm volatile (
        "mrc p15, 0, r0, c0, c0, 5\n" // Читаем MPIDR (Multiprocessor Affinity Register)
        "ands r0, r0, #3\n"           // Маскируем ID ядра (0, 1, 2 или 3)
        "bne .halt\n"                 // Если не ядро 0 — в бесконечный цикл
        "mov sp, #0x8000\n"
        "bl main\n"
        ".halt: wfe\n"
        "b .halt\n"
    );
}


void delay(int count) {
    while(count--) {
        // nop (No Operation) не дает компилятору вырезать этот цикл при оптимизации
        asm volatile("nop"); 
    }

}

void main() {
    // Настраиваем GPIO 21 как Output.
    // Очищаем биты 3-5 (маска 111 в двоичном = 7, сдвигаем на 3)
    GPFSEL2 &= ~(7 << 27); 
    // Записываем 001 в биты 3-5
    GPFSEL2 |= (1 << 27);  

    // Бесконечный цикл моргания

        for(;;) {
            GPCLR0 = (1 << 29);  // Выключить ток на GPIO 21
            delay(2000000);
            GPSET0 = (1 << 29); 
            delay(2000000);
            
        }
    
}