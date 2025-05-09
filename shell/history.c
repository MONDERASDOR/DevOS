#include <string.h>
#define HISTORY_SIZE 32
#define CMD_LEN 128
static char history[HISTORY_SIZE][CMD_LEN];
static int count = 0;

void history_add(const char *cmd) {
    strncpy(history[count % HISTORY_SIZE], cmd, CMD_LEN-1);
    history[count % HISTORY_SIZE][CMD_LEN-1] = 0;
    count++;
}

const char* history_get(int idx) {
    if (idx < 0 || idx >= count || idx >= HISTORY_SIZE) return NULL;
    return history[idx];
}

void history_clear() {
    memset(history, 0, sizeof(history));
    count = 0;
}
