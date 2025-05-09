#ifndef WM_H
#define WM_H

#include "terminal.h"
extern int active_terminal;

void wm_statusbar();
void wm_draw_terminal(int idx);
void term_putc(struct terminal* t, char c);
void term_print(struct terminal* t, const char* s);
void terminal_shell(struct terminal* t);
void wm_start();

#endif // WM_H
