#include "root_manager.h"
#include <stdlib.h>

// A simple dynamic array for root pointers
static void*** roots = NULL;
static size_t root_count = 0;
static size_t root_capacity = 0;

void rm_init() {
    root_capacity = 10;
    roots = (void***)malloc(root_capacity * sizeof(void**));
}

void rm_add_root(void** root) {
    if (root_count == root_capacity) {
        root_capacity *= 2;
        roots = (void***)realloc(roots, root_capacity * sizeof(void**));
    }
    roots[root_count++] = root;
}

void rm_remove_root(void** root) {
    for (size_t i = 0; i < root_count; ++i) {
        if (roots[i] == root) {
            roots[i] = roots[--root_count];
            return;
        }
    }
}

void** rm_get_roots(size_t* count) {
    *count = root_count;
    return (void**)roots;
}

void rm_shutdown() {
    free(roots);
}
