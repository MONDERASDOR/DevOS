#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: calc <add|sub|mul|div> <a> <b>\n");
        return 1;
    }
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    if (strcmp(argv[1], "add") == 0) printf("%d\n", a + b);
    else if (strcmp(argv[1], "sub") == 0) printf("%d\n", a - b);
    else if (strcmp(argv[1], "mul") == 0) printf("%d\n", a * b);
    else if (strcmp(argv[1], "div") == 0 && b != 0) printf("%d\n", a / b);
    else printf("Invalid op or zero division\n");
    return 0;
}
