#include "cmocka_allocator.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

static void * _cmocka_allocate(const size_t num, const size_t size, const char * file, const int line) {
    return _test_calloc(num, size, file, line);
}

static void _cmocka_free(void ** pointer, char const * const file, int const line) {
    _test_free(*pointer, file, line);
}

static void _cmocka_free_safe(void ** pointer, const size_t size, char const * const file, int const line) {
    memset(*pointer, 0, size);
    _test_free(*pointer, file, line);
}

static void _cmocka_free_immediate(void ** pointer, const char * file, const int line) {
    _cmocka_free(pointer, file, line);
}

static void _cmocka_free_immediate_safe(void ** pointer, size_t size, const char * file, const int line) {
    _cmocka_free_safe(pointer, size, file, line);
}

static const struct memory_operations _cmocka_operations = {
    .allocate = &_cmocka_allocate,
    .release = &_cmocka_free,
    .release_safe = &_cmocka_free_safe,
    .release_immediate = &_cmocka_free_immediate,
    .release_immediate_safe = &_cmocka_free_immediate_safe
};

static const struct allocator_operations _cmocka_allocator = {
    .memory_operations = &_cmocka_operations
};

const struct allocator_operations * cmocka_allocator_operations = &_cmocka_allocator;
