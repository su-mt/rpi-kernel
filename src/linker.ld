ENTRY(_enter)

MEMORY {
    ram (rwx) : ORIGIN = 0x8000, LENGTH = 256M
}

SECTIONS {
    . = 0x8000;
    .text : {
        PROVIDE (__TEXT_START__ = .);
        KEEP(*(.text._enter))
        *(.text*)
        *(text.*)
        PROVIDE (__TEXT_END__ = .);
    } > ram

    .rodata : {
        *(.rodata*)
    } > ram

    .data : {
        *(.data*)
    } > ram

    .bss (NOLOAD) : {
        *(.bss*)
        *(COMMON)
    } > ram

    . = ALIGN(8);
    PROVIDE(end = .);
    PROVIDE(_end = .);
    PROVIDE(__end__ = .);
}