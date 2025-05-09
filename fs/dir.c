#include <stdio.h>
#include <string.h>
#define MAX_DIRS 16
#define MAX_DNAME 32

struct dir {
    char name[MAX_DNAME];
    int used;
};

static struct dir dirs[MAX_DIRS];

void dir_init() {
    memset(dirs, 0, sizeof(dirs));
}

int dir_create(const char *name) {
    for (int i = 0; i < MAX_DIRS; i++) {
        if (!dirs[i].used) {
            strncpy(dirs[i].name, name, MAX_DNAME-1);
            dirs[i].used = 1;
            return i;
        }
    }
    return -1;
}

void dir_list() {
    printf("Directories:\n");
    for (int i = 0; i < MAX_DIRS; i++) {
        if (dirs[i].used) printf("- %s\n", dirs[i].name);
    }
}
