#include <time.h>
#include <stdio.h>

void clock_now() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    printf("%02d:%02d:%02d\n", tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
}
