#include <stdio.h>
#include "../include/syscall.h"

int main() {
    int ms = syscall(SYS_TIME, NULL);
    printf("System time: %d ms\n", ms);
    return 0;
}
