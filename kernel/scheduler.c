#include "../include/scheduler.h"
#include "../include/process.h"
#include "../include/string.h"
#include "../include/stdio.h"
#include "../include/log.h"

static int current = 0;
extern struct process process_table[MAX_PROCESSES];
extern int process_count;

void scheduler_init() {
    kprint("[scheduler] Initialized\n");
    log_msg(LOG_INFO, "[scheduler] Initialized");
    current = 0;
}

void scheduler_add_process(void (*entry)(), const char *name) {
    process_create(name, entry);
    log_msg(LOG_INFO, "[scheduler] Added process.");
kprint(name);
kprint("\n");
}

void scheduler_tick() {
    if (process_count == 0) return;
    current = (current + 1) % process_count;
    if (process_table[current].running) {
        process_table[current].entry();
    }
}

void scheduler_run() {
    while (1) {
        scheduler_tick();
    }
}
