// Minimal kernel-compatible string functions
#include "../include/string.h"

int k_strcmp(const char* a, const char* b) {
    while (*a && (*a == *b)) { a++; b++; }
    return *(const unsigned char*)a - *(const unsigned char*)b;
}

int k_strncmp(const char* a, const char* b, int n) {
    while (n && *a && (*a == *b)) { a++; b++; n--; }
    if (n == 0) return 0;
    return *(const unsigned char*)a - *(const unsigned char*)b;
}

void k_memset(void *dest, int c, int n) {
    unsigned char *d = dest;
    for (int i = 0; i < n; i++) d[i] = (unsigned char)c;
}

void k_strncpy(char *dest, const char *src, int n) {
    int i = 0;
    for (; i < n && src[i]; i++) dest[i] = src[i];
    for (; i < n; i++) dest[i] = 0;
}

int k_atoi(const char *s) {
    int n = 0;
    while (*s >= '0' && *s <= '9') n = n * 10 + (*s++ - '0');
    return n;
}

char *k_strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
    return n;
}
