#include "libc_allocator.h"
#include <string.h>

extern void * __real_malloc(const size_t size);
extern void * __real_calloc(const size_t num, const size_t size);
extern void __real_free(void * pointer);

static void * _libc_wrapper_calloc(size_t num, size_t size) {
    void * result = __real_calloc(num, size);
    return result;
}

static void * _libc_wrapper_malloc(size_t size) {
    void * result = __real_malloc(size);
    return result;
}

static void _libc_wrapper_free(void *ptr) {
    __real_free(ptr);
}


static void * _libc_allocate(size_t num, size_t size, const char * file, const int line) {
    (void) file;
    (void) line;

    return _libc_wrapper_calloc(num, size);
}

static void _libc_free(void ** pointer, const char * file, const int line) {
    (void) file;
    (void) line;

    _libc_wrapper_free(*pointer);
    *pointer = 0;
}

static void _libc_free_safe(void ** pointer, size_t size, const char * file, const int line) {
    (void) file;
    (void) line;

    memset(*pointer, 0, size);
    _libc_wrapper_free(*pointer);
    *pointer = 0;
}

static void _libc_free_immediate(void ** pointer, const char * file, const int line) {
    _libc_free(pointer, file, line);
}

static void _libc_free_immediate_safe(void ** pointer, size_t size, const char * file, const int line) {
    _libc_free_safe(pointer, size, file, line);
}

static const struct memory_operations _libc_operations = {
    .allocate = &_libc_allocate,
    .free = &_libc_free,
    .free_safe = &_libc_free_safe,
    .free_immediate = &_libc_free_immediate,
    .free_immediate_safe = &_libc_free_immediate_safe
};

static const struct allocator_operations _libc_allocator = {
    .memory_operations = &_libc_operations,
    .wrap_malloc = _libc_wrapper_malloc,
    .wrap_calloc = _libc_wrapper_calloc,
    .wrap_free = _libc_wrapper_free
};

struct allocator_operations const * libc_allocator_operations = &_libc_allocator;
