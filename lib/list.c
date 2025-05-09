#include "../include/k_memory.h"

struct list_node {
    void *data;
    struct list_node *prev, *next;
};

struct list {
    struct list_node *head, *tail;
};

void list_init(struct list *l) {
    l->head = l->tail = NULL;
}

void list_push_back(struct list *l, void *data) {
    struct list_node *n = k_malloc(sizeof(struct list_node));
    n->data = data;
    n->next = NULL;
    n->prev = l->tail;
    if (l->tail) l->tail->next = n;
    else l->head = n;
    l->tail = n;
}

void *list_pop_front(struct list *l) {
    if (!l->head) return NULL;
    struct list_node *n = l->head;
    void *data = n->data;
    l->head = n->next;
    if (l->head) l->head->prev = NULL;
    else l->tail = NULL;
    k_free(n);
    return data;
}
