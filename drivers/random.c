#include <stdlib.h>
#include <time.h>

void random_init() {
    srand((unsigned int)time(NULL));
}

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}
