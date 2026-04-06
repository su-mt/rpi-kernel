#include "uart.h"
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "printf.h"

extern int errno;

int _close(int file) { return -1; }

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) { return 1; }

int _lseek(int file, int ptr, int dir) { return 0; }

int _getpid(void) { return 1; }

int _kill(int id, int sig) {
    errno = EINVAL;
    return -1;
}

void _exit(int status) {
    while (1); 
}

int _read(int file, char *ptr, int len) {
    
    return 0; 
}

__attribute__((weak)) 
int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        UART_putchar(ptr[i]);
    }
    return len;
}


// extern char _end;        
// static char *heap_ptr = &_end;

// caddr_t _sbrk(int incr) {
//     char *prev = heap_ptr;
//     heap_ptr += incr;
//     return (caddr_t)prev;
// }
caddr_t _sbrk(int incr) {
    return (caddr_t)NULL;
}

void _putchar(char c) {
    UART_putchar(c);
}