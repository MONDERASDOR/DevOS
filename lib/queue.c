#include "../include/k_memory.h"
#include <string.h>

struct queue_node {
    void *data;
    struct queue_node *next;
};

struct queue {
    struct queue_node *head, *tail;
};

void queue_init(struct queue *q) {
    q->head = q->tail = NULL;
}

void queue_push(struct queue *q, void *data) {
    struct queue_node *n = k_malloc(sizeof(struct queue_node));
    n->data = data;
    n->next = NULL;
    if (q->tail) q->tail->next = n;
    else q->head = n;
    q->tail = n;
}

void *queue_pop(struct queue *q) {
    if (!q->head) return NULL;
    struct queue_node *n = q->head;
    void *data = n->data;
    q->head = n->next;
    if (!q->head) q->tail = NULL;
    k_free(n);
    return data;
}
