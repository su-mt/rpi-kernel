


extern void main();
extern void led_blink();
void _Exit(int exit_code) __attribute__((noreturn, noinline));


#if 0
__attribute__((naked, section(".text._enter")))
void _enter(void) {
asm volatile(
    // Проверяем текущий режим
    "mrs r0, cpsr\n"
    "and r0, r0, #0x1F\n"
    "cmp r0, #0x1A\n"          // 0x1A = HYP mode
    "bne .not_hyp\n"

    // Мы в HYP — делаем eret в SVC
    "mrs r0, cpsr\n"
    "bic r0, r0, #0x1F\n"
    "orr r0, r0, #0x13\n"      // SVC mode
    "orr r0, r0, #0xC0\n"      // IRQ+FIQ disable
    "msr spsr_hyp, r0\n"
    "ldr lr, =.after_eret\n"   // куда вернуться после eret
    "msr elr_hyp, lr\n"
    "eret\n"                    // прыжок в SVC mode

    ".after_eret:\n"
    ".not_hyp:\n"

    // Дальше — обычная инициализация в SVC/PL1
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
    ".halt:\n"
    "   wfe\n"
    "   b .halt\n"
);
}
#endif


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


__attribute__((naked))
void core1_init() {
    asm volatile (
        "mov sp, #0x400000\n"
        "bl led_blink\n"
        "b .halt\n"
    );
    
}


