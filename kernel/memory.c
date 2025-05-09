#include "../include/memory.h"
#include "../include/k_memory.h"
#include "../include/log.h"

void memory_init() {
    log_msg(LOG_INFO, "[memory] Memory manager initialized");
}

void *kmalloc(unsigned int size) {
    void *ptr = k_malloc(size);
    log_msg(LOG_INFO, "[memory] kmalloc");
    // Optionally print size and ptr with kprint if needed
    return ptr;
}

void kfree(void *ptr) {
    log_msg(LOG_INFO, "[memory] kfree");
    // Optionally print ptr with kprint if needed
    k_free(ptr);
}
