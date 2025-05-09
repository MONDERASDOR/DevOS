#ifndef MEMORY_H
#define MEMORY_H

void memory_init();
void *kmalloc(unsigned int size);
void kfree(void *ptr);

#endif // MEMORY_H
