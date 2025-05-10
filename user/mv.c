#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fs.h>

void mv(const char *src, const char *dest) {
    if (src == NULL || dest == NULL) {
        printf("Usage: mv <source_file> <destination_file>\n");
        return;
    }

    if (move_file(src, dest) == 0) {
        printf("File moved successfully from '%s' to '%s'\n", src, dest);
    } else {
        printf("Failed to move file\n");
    }
}

// Register this command
COMMAND(mv, "Move a file");
