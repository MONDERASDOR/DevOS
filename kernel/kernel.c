#include "../include/kernel.h"
#include "../include/scheduler.h"
#include "../include/process.h"
#include "../include/k_memory.h"
#include "../include/stdio.h"
#include "../include/log.h"
#include "../include/vga.h"

void k_vga_clear() {}
#include "../include/stdio.h"
#include "../include/timer.h"


void kernel_main(void) {
    k_vga_clear();
    kprint("[kernel] Booting devOS...\n");
    kernel_init();
    // Main kernel loop (halt CPU)
    while (1) { __asm__("hlt"); }
}

void kernel_init() {
    log_init();
    k_memory_init();
    process_init();
    scheduler_init();
    timer_init();
    kprint("[kernel] devOS kernel fully initialized.\n");
}

// IF YOU ARE SEEING THIS ! ..... thank you (: