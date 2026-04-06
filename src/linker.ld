ENTRY(_enter)

MEMORY {
    ram (rwx) : ORIGIN = 0x8000, LENGTH = 256M
}

SECTIONS {
    .text : {
        PROVIDE (__TEXT_START__ = .);
        KEEP(*(.text._enter))
        *(.text*)
        *(text.*)
        PROVIDE (__TEXT_END__ = .);
    } > ram

}