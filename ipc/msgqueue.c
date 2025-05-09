#include <stdio.h>
#include "../include/string.h"
#define MSGQ_SIZE 16
#define MSG_LEN 64

struct msg {
    char data[MSG_LEN];
};

struct msgqueue {
    struct msg queue[MSGQ_SIZE];
    int head, tail, count;
};

void msgqueue_init(struct msgqueue *q) {
    k_memset(q, 0, sizeof(*q));
}

int msgqueue_send(struct msgqueue *q, const char *msg) {
    if (q->count == MSGQ_SIZE) return -1;
    k_strncpy(q->queue[q->tail].data, msg, MSG_LEN-1);
    q->tail = (q->tail + 1) % MSGQ_SIZE;
    q->count++;
    return 0;
}

int msgqueue_recv(struct msgqueue *q, char *out) {
    if (q->count == 0) return -1;
    k_strncpy(out, q->queue[q->head].data, MSG_LEN-1);
    q->head = (q->head + 1) % MSGQ_SIZE;
    q->count--;
    return 0;
}
