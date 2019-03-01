#include "square.h"
#include <stdlib.h>
#include "entities_private.h"

static struct square * _new_square() {
    struct square * square = (struct square *) calloc(1, sizeof(struct square));
    return square;
}

static void _free_square(struct square * square) {
    free(square);
}

struct square * (*new_square)(void) = &_new_square;
void (*free_square)(struct square *) = &_free_square;

static void _set_side(struct rectangle * const rectangle, int size) {
    rectangle_ns->set_width(rectangle, size);
    rectangle_ns->set_height(rectangle, size);
}

static void _set_square_size(struct square * const square, int size) {
    _set_side((struct rectangle *) square, size);
}

static int _get_height(struct rectangle * const rectangle) {
    return rectangle_ns->get_height(rectangle);
}

static void _set_height(struct rectangle * const rectangle, int height) {
    _set_side(rectangle, height);
}

static int _get_width(struct rectangle * const rectangle) {
    return rectangle_ns->get_width(rectangle);
}

static void _set_width(struct rectangle * const rectangle, int width) {
    _set_side(rectangle, width);
}

static const struct square_operations _square_operations = {
    .base = {
        .get_height = &_get_height,
        .set_height = &_set_height,
        .get_width = &_get_width,
        .set_width = &_set_width
    },
    .set_side = _set_square_size
};

const struct square_operations * const square_ns = &_square_operations;
