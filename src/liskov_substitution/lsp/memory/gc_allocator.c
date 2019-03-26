#include "gc_allocator.h"
#include <string.h>
#include <gc.h>

static void * _gc_wrapper_calloc(size_t num, size_t size) {
    void * result = GC_malloc(num * size);
    return result;
}

static void * _gc_wrapper_malloc(size_t size) {
    void * result = GC_malloc(size);
    return result;
}

static void _gc_wrapper_free(void * pointer) {
    (void) pointer;
}

static void _gc_wrapper_free_immediate(void * pointer) {
    GC_free(pointer);
}

static void * _gc_allocate(size_t num, size_t size, const char * file, const int line) {
    (void) file;
    (void) line;

    return _gc_wrapper_calloc(num, size);
}

static void _gc_free(void ** pointer, const char * file, const int line) {
    (void) file;
    (void) line;

    _gc_wrapper_free(*pointer);
    *pointer = 0;
}

static void _gc_free_safe(void ** pointer, size_t size, const char * file, const int line) {
    (void) file;
    (void) line;

    memset(*pointer, 0, size);
    _gc_wrapper_free(*pointer);
    *pointer = 0;
}

static void _gc_free_immediate(void ** pointer, const char * file, const int line) {
    (void) file;
    (void) line;

    _gc_wrapper_free_immediate(*pointer);
    *pointer = 0;
}

static void _gc_free_immediate_safe(void ** pointer, size_t size, const char * file, const int line) {
    (void) file;
    (void) line;

    memset(*pointer, 0, size);
    _gc_wrapper_free_immediate(*pointer);
    *pointer = 0;
}


static const struct memory_operations _gc_operations = {
    .allocate = &_gc_allocate,
    .release = &_gc_free,
    .release_safe = &_gc_free_safe,
    .release_immediate = &_gc_free_immediate,
    .release_immediate_safe = &_gc_free_immediate_safe
};

static const struct allocator_operations _gc_allocator = {
    .memory_operations = &_gc_operations,
    .wrap_malloc = &_gc_wrapper_malloc,
    .wrap_calloc = &_gc_wrapper_calloc,
    .wrap_free = &_gc_wrapper_free
};


const struct allocator_operations * gc_allocator_operations = &_gc_allocator;
