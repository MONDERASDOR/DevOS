#include "../include/process.h"
#include "../include/string.h"
#include "../include/stdio.h"

#ifndef NULL
#define NULL 0
#endif

struct process process_table[MAX_PROCESSES];
int process_count = 0;

void process_init() {
    process_count = 0;
    k_memset(process_table, 0, sizeof(process_table));
}

struct process *process_create(const char *name, void (*entry)()) {
    if (process_count >= MAX_PROCESSES) return NULL;
    struct process *p = &process_table[process_count];
    p->pid = process_count + 1;
    k_strncpy(p->name, name, 31);
    p->name[31] = 0;
    p->entry = entry;
    p->running = 1;
    process_count++;
    return p;
}

void process_kill(int pid) {
    for (int i = 0; i < process_count; i++) {
        if (process_table[i].pid == pid) {
            process_table[i].running = 0;
        }
    }
}

void process_list() {
    kprint("PID\tNAME\tRUNNING\n");
    for (int i = 0; i < process_count; i++) {
        kprint("PID: ");
        char pid_buf[12];
k_itoa(process_table[i].pid, pid_buf);
kprint(pid_buf);
        kprint("\t");
        kprint(process_table[i].name);
        kprint("\tRUNNING: ");
        char run_buf[12];
k_itoa(process_table[i].running, run_buf);
kprint(run_buf);
        kprint("\n");
    }
}

struct process *process_get(int pid) {
    for (int i = 0; i < process_count; i++) {
        if (process_table[i].pid == pid) return &process_table[i];
    }
    return NULL;
}
