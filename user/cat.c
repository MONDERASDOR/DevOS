#include <stdio.h>
#include "../fs/file.c"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: cat <file>\n");
        return 1;
    }
    int fd = file_open(argv[1]);
    if (fd < 0) {
        printf("No such file: %s\n", argv[1]);
        return 1;
    }
    printf("%s\n", file_read(fd));
    return 0;
}
