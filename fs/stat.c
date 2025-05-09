#include <stdio.h>
#include <string.h>

struct stat {
    char name[32];
    int size;
    int is_dir;
};

void stat_print(const struct stat *s) {
    printf("%s\t%d\t%s\n", s->name, s->size, s->is_dir ? "DIR" : "FILE");
}
