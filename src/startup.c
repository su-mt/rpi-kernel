


extern void main();
extern void led_blink();
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

__attribute__((naked))
void core1_init() {
    asm volatile (
        "mov sp, #0x400000\n"
        "bl led_blink\n"
        "b .halt\n"
    );
    
}


