#include <stdio.h>
#include <string.h>
#define MAX_FILES 32
#define MAX_NAME 32
#define MAX_CONTENT 256

struct file {
    char name[MAX_NAME];
    char content[MAX_CONTENT];
    int used;
};

static struct file files[MAX_FILES];

void fs_init() {
    memset(files, 0, sizeof(files));
}

int fs_create(const char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (!files[i].used) {
            strncpy(files[i].name, name, MAX_NAME-1);
            files[i].used = 1;
            files[i].content[0] = 0;
            return i;
        }
    }
    return -1;
}

int fs_write(int fd, const char *data) {
    if (fd < 0 || fd >= MAX_FILES || !files[fd].used) return -1;
    strncpy(files[fd].content, data, MAX_CONTENT-1);
    return 0;
}

const char* fs_read(int fd) {
    if (fd < 0 || fd >= MAX_FILES || !files[fd].used) return NULL;
    return files[fd].content;
}

void fs_list() {
    printf("Files:\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].used) printf("- %s\n", files[i].name);
    }
}
