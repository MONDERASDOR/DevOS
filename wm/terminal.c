#include "../include/terminal.h"
#include "../include/command.h"

// Minimal kernel-compatible terminal implementation for devOS WM

#include "../include/terminal.h"
#include "../include/command.h"

extern int keyboard_read(char *buf, int maxlen);
extern void command_exec(const char *cmd);
extern void term_print(struct terminal* t, const char* s);
extern void wm_draw_terminal(int idx);
#include "../include/wm.h"

void terminal_init(struct terminal* t) {
    for (int y = 0; y < TERM_ROWS; y++)
        for (int x = 0; x < TERM_COLS; x++)
            t->buffer[y][x] = ' ';
    t->row = 1;
    t->col = 0;
}

void terminal_handle_input(struct terminal* t) {
    char cmd[128];
    while (1) {
        term_print(t, "> ");
        wm_draw_terminal(active_terminal);
        int len = keyboard_read(cmd, 127);
        cmd[len] = 0;
        // Manual string compare for "exit"
        if (len == 4 && cmd[0] == 'e' && cmd[1] == 'x' && cmd[2] == 'i' && cmd[3] == 't') break;
        command_exec(cmd);
    }
}

