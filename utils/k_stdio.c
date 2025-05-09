#include "../include/stdio.h"
#include "../include/vga.h"

void kprint(const char *fmt) {
    while (*fmt) {
        vga_putc(*fmt++);
    }
}
