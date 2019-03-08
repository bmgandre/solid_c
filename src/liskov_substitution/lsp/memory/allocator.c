#include "allocator.h"
#include <malloc.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <gc.h>

typedef void * (*malloc_func)(const size_t size);
typedef void * (*calloc_func)(const size_t num, const size_t size);
typedef void (*free_func)(void * pointer);

static void * _gc_wrapper_calloc(size_t num, size_t size) {
    void * result = GC_malloc(num * size);
    return result;
}

static void * _gc_wrapper_malloc(size_t size) {
    void * result = GC_malloc(size);
    return result;
}

static void _gc_wrapper_free(void *ptr) {
    (void) ptr;
}

static void * _std_wrapper_calloc(size_t num, size_t size) {
    void * result = calloc(num, size);
    return result;
}

static void * _std_wrapper_malloc(size_t size) {
    void * result = malloc(size);
    return result;
}

static void _std_wrapper_free(void *ptr) {
    free(ptr);
}

static void std_wrapper_init(void);
static void gc_wrapper_init(void);

static void * _allocate_stdlib(size_t num, size_t size, char const * const file, int const line) {
    (void) file;
    (void) line;

    return _std_wrapper_calloc(num, size);
}

static void _free_stdlib(void * pointer, char const * const file, int const line) {
    (void) file;
    (void) line;

    _std_wrapper_free(pointer);
}

static const struct allocator_operations _stdlib_allocator = {
    .allocate = &_allocate_stdlib,
    .free = &_free_stdlib
};

static void * _allocate_libgc(size_t num, size_t size, char const * const file, int const line) {
    (void) file;
    (void) line;

    return _gc_wrapper_calloc(num, size);
}

static void _free_libgc(void * pointer, char const * const file, int const line) {
    (void) file;
    (void) line;

    _gc_wrapper_free(pointer);
}

static const struct allocator_operations _libgc_allocator = {
    .allocate = &_allocate_libgc,
    .free = &_free_libgc
};

extern void * _test_malloc(const size_t size, const char* file, const int line);
extern void * _test_calloc(const size_t num, const size_t size, const char* file, const int line);
extern void _test_free(void * const ptr, const char* file, const int line);

static void * _allocate_cmocka(const size_t num, const size_t size, const char * file, const int line) {
    return _test_calloc(num, size, file, line);
}

static void _free_cmocka(void * pointer, char const * const file, int const line) {
    _test_free(pointer, file, line);
}

static const struct allocator_operations _cmocka_allocator = {
    .allocate = &_allocate_cmocka,
    .free = &_free_cmocka
};

const struct allocator_operations * allocator = &_stdlib_allocator;

static void _set_allocator_stdlib() {
    std_wrapper_init();
    allocator = &_stdlib_allocator;
}

static void _set_allocator_cmocka() {
    allocator = &_cmocka_allocator;
}

static void _set_allocator_libgc() {
     gc_wrapper_init();
    allocator = &_libgc_allocator;
}

static void _set_allocator_strategy(allocator_strategy strategy) {
    switch (strategy) {
    case CMOCKA_STRATEGY:
        _set_allocator_cmocka();
        break;
    case LIBGC_STRATEGY:
        _set_allocator_libgc();
        break;
    default:
        _set_allocator_stdlib();
        break;
    }
}

void (*set_allocator_strategy)(allocator_strategy strategy) = &_set_allocator_strategy;

static malloc_func current_malloc_func = _std_wrapper_malloc;
static calloc_func current_calloc_func = _std_wrapper_calloc;
static free_func current_free_func = _std_wrapper_free;

static void std_wrapper_init() {
    current_malloc_func = _std_wrapper_malloc;
    current_calloc_func = _std_wrapper_calloc;
    current_free_func = _std_wrapper_free;
}

static void gc_wrapper_init() {
    current_malloc_func = _gc_wrapper_malloc;
    current_calloc_func = _gc_wrapper_calloc;
    current_free_func = _gc_wrapper_free;
}

void * __wrap_malloc(const size_t size) {
    return current_malloc_func(size);
}

void * __wrap_calloc(const size_t num, const size_t size) {
    return current_calloc_func(num, size);
}

void __wrap_free(void * pointer) {
    current_free_func(pointer);
}
