#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fs.h>

void cp(const char *src, const char *dest) {
    if (src == NULL || dest == NULL) {
        printf("Usage: cp <source_file> <destination_file>\n");
        return;
    }

    if (copy_file(src, dest) == 0) {
        printf("File copied successfully from '%s' to '%s'\n", src, dest);
    } else {
        printf("Failed to copy file\n");
    }
}

// Register this command
COMMAND(cp, "Copy a file");
