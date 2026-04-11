
ENTRY(_enter)


PHYS_RAM_BASE   = 0x8000;

MEMORY {
    ram (rwx) : ORIGIN = PHYS_RAM_BASE, LENGTH = 512M
}

SECTIONS {
    . = PHYS_RAM_BASE;
    __KERNEL_START__ = .;
    __VIRT_TO_PHYS_OFFSET__ = 0;

    .text : {
        PROVIDE(__TEXT_START__ = .);
        KEEP(*(.text._enter))
        *(.text .text.*)
        PROVIDE(__TEXT_END__ = .);
    } > ram

    . = ALIGN(4K);

    .rodata : {
        PROVIDE(__RODATA_START__ = .);
        *(.rodata .rodata.*)
        PROVIDE(__RODATA_END__ = .);
    } > ram

    . = ALIGN(4K);

    .data : {
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

    . = ALIGN(4K);

    .l1_table : { KEEP(*(.l1_table)) } > ram
    . = ALIGN(4K);

    .l2_table : { KEEP(*(.l2_table)) } > ram
    . = ALIGN(4K);

    .l3_table : { KEEP(*(.l3_table)) } > ram


    __KERNEL_END__ = .;
}



