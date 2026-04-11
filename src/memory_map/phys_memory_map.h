#ifndef _PHYS_MEMORY_MAP_H
#define _PHYS_MEMORY_MAP_H

// Raspberry Pi Physical Memory Map

// 0x00000000 - 0x00007FFF: Reserved for boot / GPU
#define MEM_BOOT_BASE       0x00000000
#define MEM_BOOT_END        0x00008000

// 0x00008000 - 0x1FFFFFFF: Main RAM (Kernel is loaded at 0x8000 for AArch32 or 0x80000 for AArch64)
#define MEM_RAM_BASE        0x00008000
#define MEM_RAM_END         0x1FFFFFFF

// 0x20000000 - 0x3EFFFFFF: Reserved
#define MEM_RESERVED_BASE   0x20000000
#define MEM_RESERVED_END    0x3EFFFFFF

// 0x3F000000 - 0x3FFFFFFF: Main Peripherals (BCM2837/BCM2835 Base)
#define PERIPHERAL_BASE     0x3F000000
#define PERIPHERAL_END      0x3FFFFFFF

// Auxiliary Peripherals Base (Mini UART).
// https://www.codeembedded.com/blog/raspberry_pi_bare_bone_vol_2/#auxiliary-peripherals-register-map
#define AUX_BASE                (PERIPHERAL_BASE + 0x00215000)

// Mini UART Registers
#define AUX_IRQ                 (AUX_BASE + 0x00) // Auxiliary Interrupt status
#define AUX_ENABLES             (AUX_BASE + 0x04) // Auxiliary enables
#define AUX_MU_IO_REG           (AUX_BASE + 0x40) // Mini Uart I/O Data
#define AUX_MU_IER_REG          (AUX_BASE + 0x44) // Mini Uart Interrupt Enable
#define AUX_MU_IIR_REG          (AUX_BASE + 0x48) // Mini Uart Interrupt Identify
#define AUX_MU_LCR_REG          (AUX_BASE + 0x4C) // Mini Uart Line Control
#define AUX_MU_MCR_REG          (AUX_BASE + 0x50) // Mini Uart Modem Control
#define AUX_MU_LSR_REG          (AUX_BASE + 0x54) // Mini Uart Line Status
#define AUX_MU_MSR_REG          (AUX_BASE + 0x58) // Mini Uart Modem Status
#define AUX_MU_SCRATCH          (AUX_BASE + 0x5C) // Mini Uart Scratch
#define AUX_MU_CNTL_REG         (AUX_BASE + 0x60) // Mini Uart Extra Control
#define AUX_MU_STAT_REG         (AUX_BASE + 0x64) // Mini Uart Extra Status
#define AUX_MU_BAUD_REG         (AUX_BASE + 0x68) // Mini Uart Baudrate

// 0x40000000 - 0x4000FFFF: ARM Local Peripherals (Timers, Interrupts, etc.)
#define ARM_LOCAL_PERIPHERAL_BASE 0x40000000
#define ARM_LOCAL_PERIPHERAL_END  0x4000FFFF

#endif // _PHYS_MEMORY_MAP_H
