#include <stdio.h>
#include "../include/string.h"
#define PIPE_BUF 128

struct pipe {
    char buf[PIPE_BUF];
    int read_pos, write_pos, used;
};

void pipe_init(struct pipe *p) {
    k_memset(p, 0, sizeof(*p));
}

int pipe_write(struct pipe *p, const char *data, int len) {
    int written = 0;
    for (int i = 0; i < len && p->write_pos < PIPE_BUF; i++) {
        p->buf[p->write_pos++] = data[i];
        written++;
    }
    p->used += written;
    return written;
}

int pipe_read(struct pipe *p, char *out, int len) {
    int read = 0;
    for (int i = 0; i < len && p->read_pos < p->write_pos; i++) {
        out[i] = p->buf[p->read_pos++];
        read++;
    }
    return read;
}
