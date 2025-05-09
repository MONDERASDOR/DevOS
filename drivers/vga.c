#include "../include/vga.h"
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY (uint16_t*)0xB8000

static uint16_t* const vga_buffer = VGA_MEMORY;
static int vga_row = 0, vga_col = 0;
static uint8_t vga_color = 0x0F; // White on black

static uint16_t vga_entry(char c, uint8_t color) {
    return (uint16_t) c | (uint16_t) color << 8;
}

void vga_clear() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] = vga_entry(' ', vga_color);
        }
    }
    vga_row = 0; vga_col = 0;
}

void vga_setcolor(uint8_t color) {
    vga_color = color;
}

void vga_putc(char c) {
    if (c == '\n') {
        vga_row++;
        vga_col = 0;
    } else {
        vga_buffer[vga_row * VGA_WIDTH + vga_col] = vga_entry(c, vga_color);
        vga_col++;
        if (vga_col >= VGA_WIDTH) {
            vga_col = 0;
            vga_row++;
        }
    }
    if (vga_row >= VGA_HEIGHT) {
        vga_clear();
    }
}


