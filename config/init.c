#include <stdio.h>
#include <string.h>
#include "config.h"

// Forward declaration from env.c
typedef void (*conf_set_fn)(const char*, const char*);
extern void conf_set(const char*, const char*);

void config_init() {
    // Initialize config environment (clear existing config)
    conf_set("__init__", "1");
}

void config_load(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("[config] Error: cannot open %s\n", filename);
        return;
    }
    char line[128];
    while (fgets(line, sizeof(line), f)) {
        char *eq = strchr(line, '=');
        if (eq) {
            *eq = 0;
            char *key = line;
            char *val = eq + 1;
            // Remove trailing newline from value
            char *nl = strchr(val, '\n');
            if (nl) *nl = 0;
            conf_set(key, val);
        }
    }
    fclose(f);
    printf("[config] Loaded config from %s\n", filename);
}

