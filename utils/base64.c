#include <stdint.h>
#include <string.h>
#include <stdio.h>
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(const uint8_t *in, int len, char *out) {
    int i, j;
    for (i = 0, j = 0; i < len;) {
        uint32_t octet_a = i < len ? in[i++] : 0;
        uint32_t octet_b = i < len ? in[i++] : 0;
        uint32_t octet_c = i < len ? in[i++] : 0;
        uint32_t triple = (octet_a << 16) | (octet_b << 8) | octet_c;
        out[j++] = base64_table[(triple >> 18) & 0x3F];
        out[j++] = base64_table[(triple >> 12) & 0x3F];
        out[j++] = base64_table[(triple >> 6) & 0x3F];
        out[j++] = base64_table[triple & 0x3F];
    }
    for (int k = 0; k < ((3 - len % 3) % 3); k++) out[j - 1 - k] = '=';
    out[j] = 0;
}
