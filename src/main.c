#include "gc.h"
#include <stdio.h>

int main() {
    // Initialize garbage collector with 1MB heap
    gc_init(1024 * 1024);

    // Allocate some memory
    int* a = (int*)gc_malloc(sizeof(int) * 10);
    gc_add_root((void**)&a);

    for (int i = 0; i < 10; ++i) {
        a[i] = i;
    }

    // Allocate more memory
    int* b = (int*)gc_malloc(sizeof(int) * 20);
    gc_add_root((void**)&b);

    for (int i = 0; i < 20; ++i) {
        b[i] = i * 2;
    }

    // Perform garbage collection
    gc_collect();

    // Print allocated arrays
    printf("Array a: ");
    for (int i = 0; i < 10; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("Array b: ");
    for (int i = 0; i < 20; ++i) {
        printf("%d ", b[i]);
    }
    printf("\n");

    // Remove roots and perform garbage collection
    gc_remove_root((void**)&a);
    gc_remove_root((void**)&b);
    gc_collect();

    // Shutdown garbage collector
    gc_shutdown();

    return 0;
}
