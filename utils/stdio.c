// Minimal kernel-compatible print function
#include "../include/stdio.h"
#include "../include/vga.h"

void kprint(const char *fmt) {
    // Kernel-wide print function using VGA
    while (*fmt) {
        vga_putc(*fmt++);
    }
}
    while (*fmt) {
        vga_putc(*fmt++);
    }
}
