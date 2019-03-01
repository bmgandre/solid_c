#include "rectangle.h"
#include <stdlib.h>
#include "entities_private.h"

static int _get_height(struct rectangle * const rectangle) {
    return rectangle->height;
}

static void _set_height(struct rectangle * const rectangle, int height) {
    rectangle->height = height;
}

static int _get_width(struct rectangle * const rectangle) {
    return rectangle->width;
}

static void _set_width(struct rectangle * const rectangle, int width) {
    rectangle->width = width;
}

static const struct rectangle_operations _rectangle_operations = {
    .get_height = &_get_height,
    .set_height = &_set_height,
    .get_width = &_get_width,
    .set_width = &_set_width
};

const struct rectangle_operations * const rectangle_ns = &_rectangle_operations;

static struct rectangle * _new_rectangle() {
    struct rectangle * rectangle = (struct rectangle *) calloc(1, sizeof(struct rectangle));
    return rectangle;
}

static void _free_rectangle(struct rectangle * rectangle) {
    if (rectangle) {
        free(rectangle);
    }
}

struct rectangle * (*new_rectangle)(void) = &_new_rectangle;
void (*free_rectangle)(struct rectangle *) = &_free_rectangle;
