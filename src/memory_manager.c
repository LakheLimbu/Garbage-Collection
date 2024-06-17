#include "memory_manager.h"
#include <stdlib.h>
#include <string.h>

// The heap
static Block* heap_start = NULL;
static Block* free_list = NULL;

void mm_init(size_t heap_size) {
    heap_start = (Block*)malloc(heap_size);
    if (heap_start == NULL) {
        perror("Failed to allocate heap");
        exit(EXIT_FAILURE);
    }
    heap_start->size = heap_size - sizeof(Block);
    heap_start->marked = 0;
    heap_start->next = NULL;
    free_list = heap_start;
}

void* mm_allocate(size_t size) {
    Block* current = free_list;
    Block* previous = NULL;

    while (current != NULL) {
        if (!current->marked && current->size >= size) {
            if (current->size > size + sizeof(Block)) {
                // Split the block
                Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->marked = 0;
                new_block->next = current->next;
                current->next = new_block;
                current->size = size;
            }
            current->marked = 1;
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                free_list = current->next;
            }
            return current->data;
        }
        previous = current;
        current = current->next;
    }
    return NULL; // No suitable block found
}

void mm_free(void* ptr) {
    if (ptr == NULL) return;
    Block* block = (Block*)((char*)ptr - offsetof(Block, data));
    block->marked = 0;
    block->next = free_list;
    free_list = block;
}

void mm_collect() {
    // Iterate over all blocks and free unmarked blocks
    Block* current = heap_start;
    while (current != NULL) {
        if (!current->marked) {
            mm_free(current->data);
        }
        current = (Block*)((char*)current + sizeof(Block) + current->size);
    }
}

void mm_shutdown() {
    free(heap_start);
}
