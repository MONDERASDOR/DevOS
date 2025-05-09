#include <stdio.h>
#include <string.h>
#define MAX_MOUNTS 8
#define MAX_PATH 64

struct mount {
    char path[MAX_PATH];
    int used;
};

static struct mount mounts[MAX_MOUNTS];

void mount_init() {
    memset(mounts, 0, sizeof(mounts));
}

int mount_add(const char *path) {
    for (int i = 0; i < MAX_MOUNTS; i++) {
        if (!mounts[i].used) {
            strncpy(mounts[i].path, path, MAX_PATH-1);
            mounts[i].used = 1;
            return i;
        }
    }
    return -1;
}

void mount_list() {
    printf("Mounts:\n");
    for (int i = 0; i < MAX_MOUNTS; i++) {
        if (mounts[i].used) printf("- %s\n", mounts[i].path);
    }
}
