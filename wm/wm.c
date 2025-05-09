// Minimal, clean, kernel-compatible window manager for devOS
// No standard library dependencies, no legacy or duplicate code

#include "../include/wm.h"
#include "../include/vga.h"
#include "../include/shell.h"
#include "../include/keyboard.h"
#include "../include/stdio.h"
int active_terminal = 0;

#define NUM_TERMINALS 4
static struct terminal terminals[NUM_TERMINALS];


void wm_statusbar() {
    char bar[81];
    int n = 0;
    const char* label = "[devOS WM] T1:T2:T3:T4 | Active: ";
    for (n = 0; label[n] && n < 80; n++) bar[n] = label[n];
    bar[n++] = '1' + active_terminal;
    while (n < 80) bar[n++] = ' ';
    bar[80] = 0;
    for (int i = 0; i < 80; i++) ((volatile char*)0xB8000)[i*2] = bar[i];
}

void wm_draw_terminal(int idx) {
    volatile char* vga = (volatile char*)0xB8000;
    for (int y = 1; y < TERM_ROWS; y++) {
        for (int x = 0; x < TERM_COLS; x++) {
            vga[((y*TERM_COLS)+x)*2] = terminals[idx].buffer[y][x] ? terminals[idx].buffer[y][x] : ' ';
            vga[((y*TERM_COLS)+x)*2+1] = 0x0F;
        }
    }
}

void term_putc(struct terminal* t, char c) {
    if (c == '\n') { t->row++; t->col = 0; }
    else {
        if (t->row < TERM_ROWS && t->col < TERM_COLS)
            t->buffer[t->row][t->col++] = c;
        if (t->col >= TERM_COLS) { t->col = 0; t->row++; }
    }
    if (t->row >= TERM_ROWS) t->row = 1;
}

void term_print(struct terminal* t, const char* s) {
    while (*s) term_putc(t, *s++);
}

void terminal_shell(struct terminal* t) {
    char cmd[128];
    while (1) {
        term_print(t, "> ");
        wm_draw_terminal(active_terminal);
        int len = keyboard_read(cmd, 127);
        cmd[len] = 0;
        if (len == 4 && cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'i' && cmd[3] == 't') break;
        term_print(t, "You typed: ");
        term_print(t, cmd);
        term_print(t, "\n");
    }
    term_print(t, "Shell exited.\n");
    wm_draw_terminal(active_terminal);
}

void wm_start() {
    char cmd[8];
    for (int i = 0; i < NUM_TERMINALS; i++) {
        for (int y = 0; y < TERM_ROWS; y++)
            for (int x = 0; x < TERM_COLS; x++)
                terminals[i].buffer[y][x] = ' ';
        terminals[i].row = 1; terminals[i].col = 0;
    }
    active_terminal = 0;
    wm_statusbar();
    wm_draw_terminal(active_terminal);
    while (1) {
        terminal_shell(&terminals[active_terminal]);
        // Wait for 1-4 or 'q'
        kprint("[WM] Press 1-4 to switch terminal, or 'q' to quit.\n");
        int len = keyboard_read(cmd, 2);
        if (len == 1 && cmd[0] == 'q') break;
        if (len == 1 && cmd[0] >= '1' && cmd[0] <= '4') {
            active_terminal = cmd[0] - '1';
            wm_statusbar();
            wm_draw_terminal(active_terminal);
        }
    }
    kprint("Window Manager exited.\n");
}
// END OF FILE
