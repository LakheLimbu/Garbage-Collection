#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h>

// Memory block structure
typedef struct Block {
    size_t size;
    int marked;
    struct Block* next;
    char data[1]; // Flexible array member for the data
} Block;

// Memory manager functions
void mm_init(size_t heap_size);
void* mm_allocate(size_t size);
void mm_free(void* ptr);
void mm_collect();
void mm_shutdown();

#endif // MEMORY_MANAGER_H
