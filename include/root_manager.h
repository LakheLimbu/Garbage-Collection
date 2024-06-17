#ifndef ROOT_MANAGER_H
#define ROOT_MANAGER_H

#include <stddef.h>

// Root manager functions
void rm_init();
void rm_add_root(void** root);
void rm_remove_root(void** root);
void** rm_get_roots(size_t* count);
void rm_shutdown();

#endif // ROOT_MANAGER_H
