#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../entities/rectangle.h"
#include "../entities/square.h"

struct test_context {
    struct rectangle * rectangle;
    struct rectangle_operations const * operations;
};

static int rectangle_size_test_setup(void **state) {
    struct test_context *test_context = malloc(sizeof(struct test_context));
    test_context->rectangle = new_rectangle();
    test_context->operations = rectangle_ns;
    *state = test_context;

    return 0;
}

static int rectangle_size_test_teardown(void **state) {
    struct test_context * test_context = (struct test_context *) *state;
    free_rectangle(test_context->rectangle);
    free(test_context);

    return 0;
}

static int square_size_test_setup(void **state) {
    struct test_context *test_context = malloc(sizeof(struct test_context));
    test_context->rectangle = (struct rectangle *) new_square();
    test_context->operations = (struct rectangle_operations const *) square_ns;
    *state = test_context;

    return 0;
}

static int square_size_test_teardown(void **state) {
    struct test_context * test_context = (struct test_context *) *state;
    free_square((struct square *) test_context->rectangle);
    free(test_context);

    return 0;
}

static void rectangle_size_test(void **state) {
    struct test_context * test_context = (struct test_context *) *state;

    test_context->operations->set_width(test_context->rectangle, 2);
    test_context->operations->set_height(test_context->rectangle, 10);

    assert_int_equal(test_context->operations->get_width(test_context->rectangle), 2);
    assert_int_equal(test_context->operations->get_height(test_context->rectangle), 10);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(rectangle_size_test,
                                        rectangle_size_test_setup,
                                        rectangle_size_test_teardown),
        cmocka_unit_test_setup_teardown(rectangle_size_test,
                                        square_size_test_setup,
                                        square_size_test_teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
