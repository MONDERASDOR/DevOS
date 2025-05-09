#include <stdlib.h>
#include "../include/string.h"
#define SHM_MAX 8
#define SHM_SIZE 256

static char shm_regions[SHM_MAX][SHM_SIZE];
static int shm_used[SHM_MAX];

void* shm_alloc() {
    for (int i = 0; i < SHM_MAX; i++) {
        if (!shm_used[i]) {
            shm_used[i] = 1;
            k_memset(shm_regions[i], 0, SHM_SIZE);
            return shm_regions[i];
        }
    }
    return NULL;
}

void shm_free(void *ptr) {
    for (int i = 0; i < SHM_MAX; i++) {
        if (shm_regions[i] == ptr) {
            shm_used[i] = 0;
            break;
        }
    }
}
