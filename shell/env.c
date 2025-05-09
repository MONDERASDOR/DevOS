#include "../include/string.h"
#define ENV_MAX 32
#define ENV_LEN 64
static char env_keys[ENV_MAX][ENV_LEN];
static char env_vals[ENV_MAX][ENV_LEN];
static int env_count = 0;

void env_set(const char *key, const char *val) {
    for (int i = 0; i < env_count; i++) {
        if (k_strcmp(env_keys[i], key) == 0) {
            k_strncpy(env_vals[i], val, ENV_LEN-1);
            return;
        }
    }
    if (env_count < ENV_MAX) {
        k_strncpy(env_keys[env_count], key, ENV_LEN-1);
        k_strncpy(env_vals[env_count], val, ENV_LEN-1);
        env_count++;
    }
}

const char* env_get(const char *key) {
    for (int i = 0; i < env_count; i++) {
        if (k_strcmp(env_keys[i], key) == 0) return env_vals[i];
    }
    return NULL;
}
