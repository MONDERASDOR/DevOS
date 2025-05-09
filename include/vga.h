#ifndef VGA_H
#define VGA_H
#include <stdint.h>
void vga_clear();
void vga_setcolor(uint8_t color);
void vga_putc(char c);

#endif
