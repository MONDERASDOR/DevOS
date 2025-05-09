#include <pthread.h>

struct event {
    int signaled;
    pthread_mutex_t lock;
    pthread_cond_t cond;
};

void event_init(struct event *e) {
    e->signaled = 0;
    pthread_mutex_init(&e->lock, NULL);
    pthread_cond_init(&e->cond, NULL);
}

void event_wait(struct event *e) {
    pthread_mutex_lock(&e->lock);
    while (!e->signaled)
        pthread_cond_wait(&e->cond, &e->lock);
    e->signaled = 0;
    pthread_mutex_unlock(&e->lock);
}

void event_signal(struct event *e) {
    pthread_mutex_lock(&e->lock);
    e->signaled = 1;
    pthread_cond_signal(&e->cond);
    pthread_mutex_unlock(&e->lock);
}
