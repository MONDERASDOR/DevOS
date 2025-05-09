// #include <ncurses.h>
#include <stdio.h>

void mouse_init() {
    mousemask(ALL_MOUSE_EVENTS, NULL);
}

void mouse_poll() {
    MEVENT event;
    int ch = getch();
    if (ch == KEY_MOUSE) {
        if (getmouse(&event) == OK) {
            printf("Mouse at %d,%d\n", event.x, event.y);
        }
    }
}
