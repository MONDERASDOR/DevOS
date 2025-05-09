// // Minimal kernel-compatible hotkeys module for devOS WM

// Add minimal hotkey logic or stubs here if needed for integration.
// No ncurses, no standard library dependencies.

void hotkeys_init() {}
void hotkeys_handle(int key) {}
 <ncurses.h>

int wm_handle_hotkey(int ch) {
    switch (ch) {
        case KEY_F(1): return 1;
        case KEY_F(2): return 2;
        case KEY_F(3): return 3;
        case KEY_F(4): return 4;
        default: return 0;
    }
}
