#include <string.h>
#define CONF_MAX 32
#define CONF_LEN 64
static char conf_keys[CONF_MAX][CONF_LEN];
static char conf_vals[CONF_MAX][CONF_LEN];
static int conf_count = 0;

void conf_set(const char *key, const char *val) {
    for (int i = 0; i < conf_count; i++) {
        if (strcmp(conf_keys[i], key) == 0) {
            strncpy(conf_vals[i], val, CONF_LEN-1);
            return;
        }
    }
    if (conf_count < CONF_MAX) {
        strncpy(conf_keys[conf_count], key, CONF_LEN-1);
        strncpy(conf_vals[conf_count], val, CONF_LEN-1);
        conf_count++;
    }
}

const char* conf_get(const char *key) {
    for (int i = 0; i < conf_count; i++) {
        if (strcmp(conf_keys[i], key) == 0) return conf_vals[i];
    }
    return NULL;
}
