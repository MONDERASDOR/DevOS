#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fs.h>

void rmdir(const char *path) {
    if (path == NULL) {
        printf("Usage: rmdir <directory_path>\n");
        return;
    }

    if (remove_directory(path) == 0) {
        printf("Directory '%s' removed successfully\n", path);
    } else {
        printf("Failed to remove directory '%s'\n", path);
    }
}

// Register this command
COMMAND(rmdir, "Remove a directory");
