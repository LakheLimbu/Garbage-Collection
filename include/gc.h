#ifndef GC_H
#define GC_H

#include <stddef.h>

// Initialize the garbage collector
void gc_init(size_t heap_size);

// Allocate memory with garbage collection
void* gc_malloc(size_t size);

// Free allocated memory (for manual control if needed)
void gc_free(void* ptr);

// Add a root pointer
void gc_add_root(void** root);

// Remove a root pointer
void gc_remove_root(void** root);

// Perform garbage collection
void gc_collect(void);

// Shutdown the garbage collector
void gc_shutdown(void);

#endif // GC_H
