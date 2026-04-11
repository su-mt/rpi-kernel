#ifndef VIRT_MEMORY_MAP_H
#define VIRT_MEMORY_MAP_H


#define PAGE_SIZE 4096
// Virtual Memory Map

// 0x80000000 - 0x9FFFFFFF: Direct Map (RAM). Kernel code and data.
#define VIRT_RAM_BASE               0x80008000
#define VIRT_RAM_END                0x9FFFFFFF

// 0xA0000000 - 0xFDFFFFFF: VMALLOC / Kernel stacks. Free zone.
#define VIRT_VMALLOC_BASE           0xA0000000
#define VIRT_VMALLOC_END            0xFDFFFFFF

// 0xFE000000 - 0xFEFFFFFF: Main Peripherals (GPIO, UART - mapped to physical 0x3F...)
#define VIRT_PERIPHERAL_BASE        0xFE000000
#define VIRT_PERIPHERAL_END         0xFEFFFFFF

// 0xFF000000 - 0xFF0FFFFF: Local Peripherals (Mailboxes, timers - mapped to physical 0x40...)
#define VIRT_LOCAL_PERIPHERAL_BASE  0xFF000000
#define VIRT_LOCAL_PERIPHERAL_END   0xFF0FFFFF

// 0xFFFF0000 - 0xFFFF0FFF: High Vectors
#define VIRT_HIGH_VECTORS_BASE      0xFFFF0000
#define VIRT_HIGH_VECTORS_END       0xFFFF0FFF

#endif // VIRT_MEMORY_MAP_H
