#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../entities/rectangle.h"

struct test_context {
    struct rectangle* rectangle;
};

static int setup(void **state) {
    struct test_context *test_context = malloc(sizeof(struct test_context));

    test_context->rectangle = new_rectangle();
    rectangle_ns->set_width(test_context->rectangle, 2);
    rectangle_ns->set_height(test_context->rectangle, 10);

    *state = test_context;
    return 0;
}

static int teardown(void **state) {
    struct test_context * test_context = (struct test_context *) *state;
    free_rectangle(test_context->rectangle);
    free(test_context);
    return 0;
}

static void int_test_success(void **state) {
    struct test_context * test_context = (struct test_context *) *state;

    assert_int_equal(rectangle_ns->get_width(test_context->rectangle), 2);
    assert_int_equal(rectangle_ns->get_height(test_context->rectangle), 10);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(int_test_success, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
