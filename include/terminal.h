#ifndef TERMINAL_H
#define TERMINAL_H

#define TERM_ROWS 25
#define TERM_COLS 80

struct terminal {
    char buffer[TERM_ROWS][TERM_COLS];
    int row, col;
};

void terminal_init(struct terminal* t);
void terminal_handle_input(struct terminal* t);

#endif // TERMINAL_H
