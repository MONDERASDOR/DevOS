#include "../include/shell.h"
#include "../include/string.h"
#include "../include/stdio.h"
#include "../include/vga.h"

// Minimal keyboard input (stub, to be implemented for real hardware)
extern int keyboard_read(char* buf, int maxlen);

void shell_run() {
    char cmd[128];
    while (1) {
        kprint("> ");
        int len = keyboard_read(cmd, 127);
        cmd[len] = 0;
        if (k_strcmp(cmd, "exit") == 0) break;
        kprint("You typed: ");
        kprint(cmd);
        kprint("\n");
    }
    kprint("Shell exited.\n");
}
