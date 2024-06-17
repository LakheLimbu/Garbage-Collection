#include "gc.h"
#include "memory_manager.h"
#include "root_manager.h"
#include <stddef.h>  // for offsetof
#include <stdint.h>  // for uintptr_t

void gc_init(size_t heap_size) {
    mm_init(heap_size);
    rm_init();
}

void* gc_malloc(size_t size) {
    return mm_allocate(size);
}

void gc_free(void* ptr) {
    mm_free(ptr);
}

void gc_add_root(void** root) {
    rm_add_root(root);
}

void gc_remove_root(void** root) {
    rm_remove_root(root);
}

void gc_collect() {
    size_t root_count;
    void**  roots = rm_get_roots(&root_count);
    for (size_t i = 0; i < root_count; ++i) {
        if (*roots[i] != NULL) {
            // Correctly cast the void pointer to a char pointer before arithmetic
            Block* block = (Block*)((uintptr_t)*roots[i] - offsetof(Block, data));
            block->marked = 1;
        }
    }
    mm_collect();
}

void gc_shutdown() {
    mm_shutdown();
    rm_shutdown();
}
