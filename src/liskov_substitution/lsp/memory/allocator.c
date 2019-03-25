#include "allocator.h"
#include "libc_allocator.h"
#include "gc_allocator.h"
#include "cmocka_allocator.h"

typedef void * (*malloc_func)(const size_t size);
typedef void * (*calloc_func)(const size_t num, const size_t size);
typedef void (*free_func)(void * pointer);

static malloc_func current_malloc_func = NULL;
static calloc_func current_calloc_func = NULL;
static free_func current_free_func = NULL;

static struct memory_operations const * current_memory_operations = NULL;

static void _wrapper_memory(struct allocator_operations const * const allocator_operations) {
    current_malloc_func = allocator_operations->wrap_malloc;
    current_calloc_func = allocator_operations->wrap_calloc;
    current_free_func = allocator_operations->wrap_free;
}

static void _set_allocator_libc() {
    _wrapper_memory(libc_allocator_operations);
    current_memory_operations = libc_allocator_operations->memory_operations;
}

static void _set_allocator_cmocka() {
    _wrapper_memory(cmocka_allocator_operations);
    current_memory_operations = cmocka_allocator_operations->memory_operations;
}

static void _set_allocator_libgc() {
    _wrapper_memory(gc_allocator_operations);
    current_memory_operations = gc_allocator_operations->memory_operations;
}

static void _set_allocator_strategy(memory_strategy strategy) {
    switch (strategy) {
    case ALLOCATE_STRATEGY_CMOCKA:
        _set_allocator_cmocka();
        break;
    case ALLOCATE_STRATEGY_GC:
        _set_allocator_libgc();
        break;
    default:
        _set_allocator_libc();
        break;
    }
}

void (*set_allocator_strategy)(memory_strategy strategy) = &_set_allocator_strategy;

static struct memory_operations const * _get_allocator() {
    return current_memory_operations == NULL
            ? libc_allocator_operations->memory_operations
            : current_memory_operations;
}

struct memory_operations const * (*get_allocator)(void) = &_get_allocator;

void * __wrap_malloc(const size_t size) {
    return current_malloc_func == NULL
            ? libc_allocator_operations->wrap_malloc(size)
            : current_malloc_func(size);
}

void * __wrap_calloc(const size_t num, const size_t size) {
    return current_calloc_func == NULL
            ? libc_allocator_operations->wrap_calloc(num, size)
            : current_calloc_func(num, size);
}

void __wrap_free(void * pointer) {
    if (current_free_func == NULL) {
        libc_allocator_operations->wrap_free(pointer);
    } else {
        current_free_func(pointer);
    }
}
