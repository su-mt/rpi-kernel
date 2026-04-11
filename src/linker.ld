
ENTRY(_enter)

/* Базовые адреса */
PHYS_RAM_BASE   = 0x8000;
KERNEL_OFFSET   = 0x80000000;     
VIRT_RAM_BASE   = PHYS_RAM_BASE + KERNEL_OFFSET;

MEMORY {
    ram (rwx) : ORIGIN = PHYS_RAM_BASE, LENGTH = 512M
}

SECTIONS {
    /* Начало ядра в виртуальной памяти */
    . = VIRT_RAM_BASE;
    __KERNEL_START__ = .;

    /* Смещение между виртуальными и физическими адресами */
    __VIRT_TO_PHYS_OFFSET__ = VIRT_RAM_BASE - PHYS_RAM_BASE;

    .text : AT(ADDR(.text) - __VIRT_TO_PHYS_OFFSET__) {
        PROVIDE(__TEXT_START__ = .);
        KEEP(*(.text._enter))
        *(.text .text.*)
        PROVIDE(__TEXT_END__ = .);
    } > ram

    . = ALIGN(4K);

    .rodata : AT(ADDR(.rodata) - __VIRT_TO_PHYS_OFFSET__) {
        PROVIDE(__RODATA_START__ = .);
        *(.rodata .rodata.*)
        PROVIDE(__RODATA_END__ = .);
    } > ram

    . = ALIGN(4K);

    .data : AT(ADDR(.data) - __VIRT_TO_PHYS_OFFSET__) {
        PROVIDE(__DATA_START__ = .);
        *(.data .data.*)
        PROVIDE(__DATA_END__ = .);
    } > ram

    . = ALIGN(4K);

    .bss (NOLOAD) : {
        PROVIDE(__BSS_START__ = .);
        *(.bss .bss.*)
        *(COMMON)
        PROVIDE(__BSS_END__ = .);
    } > ram

    .pajes : {
        PROVIDE(__PAGES_START__ = .);
        *(*.pgs)
        PROVIDE(__PAGES_END__ = .);
    } > ram


    __KERNEL_END__ = .;
}

