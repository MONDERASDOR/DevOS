// Minimal kernel-safe string functions

int k_strlen(const char *s) {
    size_t n = 0;
    while (s && *s++) n++;
    return n;
}

char *k_strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
}

int k_strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) { a++; b++; }
    return *(unsigned char*)a - *(unsigned char*)b;
}

// Minimal integer to string conversion
char *k_itoa(int value, char *buf) {
    int i = 0, sign = value;
    if (value < 0) value = -value;
    do {
        buf[i++] = (value % 10) + '0';
        value /= 10;
    } while (value);
    if (sign < 0) buf[i++] = '-';
    buf[i] = '\0';
    // Reverse
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char tmp = buf[j]; buf[j] = buf[k]; buf[k] = tmp;
    }
    return buf;
}

// removed strcat (not kernel-safe)(char *dest, const char *src) {
    char *d = dest + strlen(dest);
    while ((*d++ = *src++));
    return dest;
}
