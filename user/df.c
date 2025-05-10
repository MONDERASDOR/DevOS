#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fs.h>

void df(void) {
    struct fs_stat stat;
    if (get_fs_stats(&stat) == 0) {
        printf("File System Usage:\n");
        printf("-----------------\n");
        printf("Total: %lu KB\n", stat.total_size / 1024);
        printf("Used: %lu KB\n", stat.used_size / 1024);
        printf("Free: %lu KB\n", stat.free_size / 1024);
        printf("%d%% used\n", (int)((stat.used_size * 100) / stat.total_size));
    } else {
        printf("Failed to get file system statistics\n");
    }
}

// Register this command
COMMAND(df, "Show file system disk space usage");
