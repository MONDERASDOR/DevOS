#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fs.h>

void mkdir(const char *path) {
    if (path == NULL) {
        printf("Usage: mkdir <directory_path>\n");
        return;
    }

    if (create_directory(path) == 0) {
        printf("Directory '%s' created successfully\n", path);
    } else {
        printf("Failed to create directory '%s'\n", path);
    }
}

// Register this command
COMMAND(mkdir, "Create a new directory");
