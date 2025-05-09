#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
void uuid_v4(char *out) {
    srand((unsigned int)time(NULL));
    uint32_t data[4];
    for (int i = 0; i < 4; i++) data[i] = rand();
    sprintf(out, "%08x-%04x-%04x-%04x-%012x",
        data[0], (data[1] >> 16) & 0xFFFF, (data[1]) & 0xFFFF,
        (data[2] >> 16) & 0xFFFF, ((uint64_t)data[2] << 32 | data[3]) & 0xFFFFFFFFFFFF);
}
