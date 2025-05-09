// #include <ncurses.h>
#include "../include/log.h"

void screen_init() {
    log_msg(LOG_INFO, "[screen] Screen initialized (kernel mode)");
}

void screen_end() {
    log_msg(LOG_INFO, "[screen] Screen ended");
}
