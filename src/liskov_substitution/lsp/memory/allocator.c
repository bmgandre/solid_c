#include "allocator.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <gc.h>

static void * _allocate_stdlib(size_t num, size_t size, char const * const file, int const line) {
    (void) file;
    (void) line;

    return calloc(num, size);
}

static void _free_stdlib(void * pointer, char const * const file, int const line) {
    (void) file;
    (void) line;

    free(pointer);
}

static const struct allocator_operations _stdlib_allocator = {
    .allocate = &_allocate_stdlib,
    .free = &_free_stdlib
};

static void * _allocate_libgc(size_t num, size_t size, char const * const file, int const line) {
    (void) file;
    (void) line;

    return GC_MALLOC(num * size);
}

static void _free_libgc(void * pointer, char const * const file, int const line) {
    (void) file;
    (void) line;
    (void) pointer;
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
    allocator = &_stdlib_allocator;
}

static void _set_allocator_cmocka() {
    allocator = &_cmocka_allocator;
}

static void _set_allocator_libgc() {
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
