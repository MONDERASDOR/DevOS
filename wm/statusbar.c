// // Minimal kernel-compatible status bar module for devOS WM

// Add minimal status bar logic or stubs here if needed for integration.
// No ncurses, no standard library dependencies.

void statusbar_show() {}
void statusbar_update() {}
 <ncurses.h>
// Minimal kernel-compatible status bar module for devOS WM

// Add minimal status bar logic or stubs here if needed for integration.
// No ncurses, no standard library dependencies.

void statusbar_show() {}
void statusbar_update() {}
 <time.h>

void wm_statusbar_draw(WINDOW *win) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char buf[32];
    strftime(buf, 32, "%H:%M:%S", tm_info);
    int width = getmaxx(win);
    mvwprintw(win, 0, width - 10, "[%s]", buf);
    wrefresh(win);
}
