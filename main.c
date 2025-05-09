#include <stdio.h>
#include "include/kernel.h"
#include "include/wm.h"

int main() {
    kernel_init();
    wm_start();
    return 0;
}
