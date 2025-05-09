#ifndef K_MEMORY_H
#define K_MEMORY_H

// Minimal kernel-compatible memory management stubs
void k_memory_init();
void* k_malloc(int size);
void k_free(void* ptr);

#endif // K_MEMORY_H
