#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

#define new(num, size) allocator->allocate(num, size, __FILE__, __LINE__)
#define destroy(ptr) allocator->free(ptr, __FILE__, __LINE__)

typedef struct allocator_operations {
    void* (*allocate)(const size_t num, const size_t size, const char * file, const int line);
    void (*free)(void * pointer, const char * file, const int line);
} allocator_operations;

extern const struct allocator_operations * allocator;

typedef enum allocator_strategy {
    STDLIB_STRATEGY,
    LIBGC_STRATEGY,
    CMOCKA_STRATEGY
} allocator_strategy;

extern void (*set_allocator_strategy)(allocator_strategy strategy);

extern void * __wrap_malloc(const size_t size);
extern void * __wrap_calloc(const size_t num, const size_t size);
extern void __wrap_free(void * pointer);

#endif // ALLOCATOR_H
