#include <stdio.h>
#include <string.h>
#include "fs.h"

int file_open(const char *name) {
    return fs_create(name);
}

int file_write(int fd, const char *data) {
    return fs_write(fd, data);
}

const char* file_read(int fd) {
    return fs_read(fd);
}

void file_close(int fd) {
    // No-op for in-memory
}
