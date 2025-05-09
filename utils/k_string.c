#include "../include/string.h"
#include "../include/k_memory.h"

int k_strcmp(const char* a, const char* b) {
    while (*a && (*a == *b)) { a++; b++; }
    return *(const unsigned char*)a - *(const unsigned char*)b;
}

int k_strncmp(const char* a, const char* b, int n) {
    while (n && *a && (*a == *b)) { a++; b++; n--; }
    if (n == 0) return 0;
    return *(const unsigned char*)a - *(const unsigned char*)b;
}

void k_strncpy(char *dest, const char *src, int n) {
    int i = 0;
    for (; i < n && src[i]; i++) dest[i] = src[i];
    for (; i < n; i++) dest[i] = 0;
}

void k_memset(void *dest, int c, int n) {
    unsigned char *d = dest;
    for (int i = 0; i < n; i++) d[i] = (unsigned char)c;
}

int k_atoi(const char *s) {
    int n = 0;
    while (*s >= '0' && *s <= '9') n = n * 10 + (*s++ - '0');
    return n;
}

int k_strlen(const char *s) {
    int n = 0;
    while (s && *s++) n++;
    return n;
}

char *k_strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
}

char *k_itoa(int value, char *buf) {
    int i = 0, sign = value;
    if (value < 0) value = -value;
    do {
        buf[i++] = (value % 10) + '0';
        value /= 10;
    } while (value);
    if (sign < 0) buf[i++] = '-';
    buf[i] = '\0';
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char tmp = buf[j]; buf[j] = buf[k]; buf[k] = tmp;
    }
    return buf;
}

// Optionally implement k_strdup if needed
char *k_strdup(const char *src) {
    int len = k_strlen(src);
    char *dst = (char*)k_malloc(len+1);
    if (!dst) return 0;
    k_strcpy(dst, src);
    return dst;
}
