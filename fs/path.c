#include <string.h>
#include <stdio.h>

void path_normalize(const char *input, char *output, int maxlen) {
    int j = 0;
    for (int i = 0; input[i] && j < maxlen-1; i++) {
        if (input[i] == '/' && (i == 0 || input[i-1] == '/')) continue;
        output[j++] = input[i];
    }
    output[j] = 0;
}
