#include "../include/log.h"
#include "../include/stdio.h"


void log_init() {
    // No-op for now, could redirect to file
}

void log_msg(int level, const char *fmt) {
    const char *lvl = (level == LOG_INFO) ? "INFO" : (level == LOG_WARN) ? "WARN" : "ERR";
    kprint("[");
kprint(lvl);
kprint("] ");
    kprint(fmt);
    kprint("\n");
}
