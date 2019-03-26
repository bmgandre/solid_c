#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

#define new(num, size) get_allocator()->allocate((num), (size), (__FILE__), (__LINE__))
#define delete(ptr) get_allocator()->release(((void**)(ptr)), (__FILE__), (__LINE__))
#define delete_safe(ptr, size) get_allocator()->release_safe(((void**)(ptr)), (size), (__FILE__), (__LINE__))
#define delete_immediate(ptr) get_allocator()->release_immediate(((void**)(ptr)), (__FILE__), (__LINE__))
#define delete_immediate_safe(ptr, size) get_allocator()->release_immediate_safe(((void**)(ptr)), (size), (__FILE__), (__LINE__))

typedef struct memory_operations {
    void* (*allocate)(const size_t num, const size_t size, const char * file, const int line);

    void (*release)(void ** pointer, const char * file, const int line);
    void (*release_safe)(void ** pointer, const size_t size, const char * file, const int line);

    void (*release_immediate)(void ** pointer, const char * file, const int line);
    void (*release_immediate_safe)(void ** pointer, const size_t size, const char * file, const int line);
} memory_operations;

extern struct memory_operations const * (*get_allocator)(void);

typedef struct allocator_operations {
    struct memory_operations const * const memory_operations;

    void * (*const wrap_malloc)(const size_t size);
    void * (*const wrap_calloc)(const size_t num, const size_t size);
    void (*const wrap_free)(void * pointer);
} alllocator_operations;

typedef enum memory_strategy {
    ALLOCATE_STRATEGY_LIBC,
    ALLOCATE_STRATEGY_GC,
    ALLOCATE_STRATEGY_CMOCKA
} memory_strategy;

extern void (*set_allocator_strategy)(memory_strategy strategy);

void * wrap_malloc(const size_t size);
void * wrap_calloc(const size_t num, const size_t size);
void wrap_free(void * pointer);

#ifdef WRAP_ALLOC
#define malloc wrap_malloc
#define calloc wrap_calloc
#define free wrap_free
#endif

#endif // ALLOCATOR_H
