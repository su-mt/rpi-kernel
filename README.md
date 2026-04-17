# Raspberry Pi Zero 2 W Bare-Metal Kernel

A minimal kernel for the Raspberry Pi Zero 2 W, written from scratch.

## Implemented Components

- **LPAE MMU with Virtual Address Space (2G/2G Scheme)** - Support for extended physical address space with kernel and user space separation
- **newlib Support** - Integration of the standard C library (in development)
- **UART Driver** - Serial communication support
- **GPIO Control** - GPIO port management
- **Boot Initialization** - System startup and initialization code

## Building

### Requirements
- ARM GNU Toolchain 15.2 
