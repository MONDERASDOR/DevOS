#include "../include/timer.h"

#include "../include/log.h"

static unsigned long ticks = 0;


void timer_init() {
    ticks = 0;
    log_msg(LOG_INFO, "[timer] Timer initialized");
}

void timer_tick() {
    ticks++;
}

unsigned long timer_now() {
    return ticks;
}
