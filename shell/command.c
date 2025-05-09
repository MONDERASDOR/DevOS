#include "../include/command.h"
#include "../include/builtin.h"
#include "../include/string.h"
#include "../include/stdio.h"

void command_exec(const char *cmd) {
    if (k_strcmp(cmd, "help") == 0) {
        builtin_help();
    } else if (k_strcmp(cmd, "ps") == 0) {
        builtin_ps();
    } else if (k_strncmp(cmd, "kill ", 5) == 0) {
        int pid = k_atoi(cmd + 5);
        builtin_kill(pid);
    } else {
        kprint("Unknown command.\n");
// Optionally print cmd with kprint if needed
    }
}
