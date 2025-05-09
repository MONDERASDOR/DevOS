#include "../include/builtin.h"
#include "../include/process.h"
#include "../include/stdio.h"

void builtin_help() {
    kprint("devOS shell built-ins:\n");
    kprint("  help     - Show this help message\n");
    kprint("  ps       - List processes\n");
    kprint("  kill PID - Kill process with PID\n");
}

void builtin_ps() {
    process_list();
}

void builtin_kill(int pid) {
    process_kill(pid);
    kprint("Process killed.\n");
// Optionally print pid as a string with kprint if needed
}
