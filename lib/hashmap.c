#include "../include/k_memory.h"

#define HASHMAP_SIZE 64

struct hashmap_entry {
    char *key;
    void *value;
    struct hashmap_entry *next;
};

struct hashmap {
    struct hashmap_entry *buckets[HASHMAP_SIZE];
};

unsigned int hash(const char *key) {
    unsigned int h = 0;
    while (*key) h = (h * 31) + (unsigned char)*key++;
    return h % HASHMAP_SIZE;
}

void hashmap_init(struct hashmap *hm) {
    k_memset(hm, 0, sizeof(*hm));
}

void hashmap_put(struct hashmap *hm, const char *key, void *value) {
    unsigned int idx = hash(key);
    struct hashmap_entry *e = k_malloc(sizeof(*e));
    e->key = k_strdup(key);
    e->value = value;
    e->next = hm->buckets[idx];
    hm->buckets[idx] = e;
}

void* hashmap_get(struct hashmap *hm, const char *key) {
    unsigned int idx = hash(key);
    for (struct hashmap_entry *e = hm->buckets[idx]; e; e = e->next) {
        if (k_strcmp(e->key, key) == 0) return e->value;
    }
    return NULL;
}
