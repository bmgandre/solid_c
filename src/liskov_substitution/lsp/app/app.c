#include "../memory/allocator.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <gc.h>
#include <stdio.h>
#include <string.h>

void leak_memory() {
    int * const temporary = (int*) new(1, sizeof(int));
    *temporary = 0;
}

void buffer_overflow() {
    char * memory = (char*) new(1, sizeof(int));
    memory[sizeof(int)] = '!';
    delete(&memory);
}

void buffer_underflow() {
    char * memory = (char*) new(1, sizeof(int));
    memory[-1] = '!';
    delete(&memory);
}

int main(void) {
    GC_set_find_leak(1);

    set_allocator_strategy(ALLOCATE_STRATEGY_LIBC);

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(leak_memory),
        cmocka_unit_test(buffer_overflow),
        cmocka_unit_test(buffer_underflow)
    };
    int result = cmocka_run_group_tests(tests, NULL, NULL);

    GC_gcollect();

    return result;
}
