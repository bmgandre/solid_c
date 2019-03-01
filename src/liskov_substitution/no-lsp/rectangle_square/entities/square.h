#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

struct square;

extern struct square * (*new_square)(void);
extern void (*free_square)(struct square *);

typedef struct square_operations {
    struct rectangle_operations base;

    void (*set_side)(struct square * const, int size);
} square_operations;

extern const struct square_operations * const square_ns;

#endif // SQUARE_H
