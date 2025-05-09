#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct semaphore {
    int value;
    pthread_mutex_t lock;
    pthread_cond_t cond;
};

void semaphore_init(struct semaphore *s, int value) {
    s->value = value;
    pthread_mutex_init(&s->lock, NULL);
    pthread_cond_init(&s->cond, NULL);
}

void semaphore_wait(struct semaphore *s) {
    pthread_mutex_lock(&s->lock);
    while (s->value <= 0)
        pthread_cond_wait(&s->cond, &s->lock);
    s->value--;
    pthread_mutex_unlock(&s->lock);
}

void semaphore_signal(struct semaphore *s) {
    pthread_mutex_lock(&s->lock);
    s->value++;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->lock);
}
