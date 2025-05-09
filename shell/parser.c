#include <string.h>
#include <ctype.h>

int parse_args(const char *input, char argv[][64], int max_args) {
    int argc = 0, i = 0;
    while (*input && argc < max_args) {
        while (*input && isspace(*input)) input++;
        if (!*input) break;
        int in_quote = 0, j = 0;
        if (*input == '"') { in_quote = 1; input++; }
        while (*input && (in_quote ? (*input != '"') : !isspace(*input))) {
            argv[argc][j++] = *input++;
        }
        argv[argc][j] = 0;
        argc++;
        if (in_quote && *input == '"') input++;
    }
    return argc;
}
