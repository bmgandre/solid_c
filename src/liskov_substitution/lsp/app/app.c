#include "../memory/allocator.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <gc.h>
#include <stdio.h>
#include <glib.h>

void leak_memory() {
    int * const temporary = (int*) new(1, sizeof(int));
    *temporary = 0;
}

void buffer_overflow() {
    char * const memory = (char*) new(1, sizeof(int));
    memory[sizeof(int)] = '!';
    destroy(memory);
}

void buffer_underflow() {
    char * const memory = (char*) new(1, sizeof(int));
    memory[-1] = '!';
    destroy(memory);
}

int main(void) {
    GC_set_find_leak(1);
    set_allocator_strategy(LIBGC_STRATEGY);

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(leak_memory),
        cmocka_unit_test(buffer_overflow),
        cmocka_unit_test(buffer_underflow)
    };
    int result = cmocka_run_group_tests(tests, NULL, NULL);

    GC_gcollect();

    return result;
}
