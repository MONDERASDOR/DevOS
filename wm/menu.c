// // Minimal kernel-compatible menu module for devOS WM

// Add minimal menu logic or stubs here if needed for integration.
// No ncurses, no standard library dependencies.

void menu_show() {}
void menu_hide() {}
 <ncurses.h>
// Minimal kernel-compatible menu module for devOS WM

// Add minimal menu logic or stubs here if needed for integration.
// No ncurses, no standard library dependencies.

void menu_show() {}
void menu_hide() {}
 <string.h>

void wm_menu_show(WINDOW *win) {
    char *items[] = { "Terminal", "Processes", "Files", "Quit" };
    int n = 4, choice = 0;
    while (1) {
        werase(win);
        box(win, 0, 0);
        for (int i = 0; i < n; i++) {
            if (i == choice) wattron(win, A_REVERSE);
            mvwprintw(win, i+1, 2, items[i]);
            if (i == choice) wattroff(win, A_REVERSE);
        }
        wrefresh(win);
        int ch = wgetch(win);
        if (ch == KEY_UP && choice > 0) choice--;
        else if (ch == KEY_DOWN && choice < n-1) choice++;
        else if (ch == 10) break;
    }
}
