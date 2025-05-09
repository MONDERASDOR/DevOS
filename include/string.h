#ifndef STRING_H
#define STRING_H

// Minimal kernel-safe string functions
// Minimal kernel-compatible string functions
int k_strcmp(const char* a, const char* b);
int k_strncmp(const char* a, const char* b, int n);
void k_memset(void *dest, int c, int n);
void k_strncpy(char *dest, const char *src, int n);
int k_atoi(const char *s);

int k_strlen(const char *s);
char *k_strcpy(char *dest, const char *src);
int k_strcmp(const char *a, const char *b);

char *k_itoa(int value, char *buf);
#endif // STRING_H
