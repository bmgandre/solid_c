#ifndef RECTANGLE_H
#define RECTANGLE_H

struct rectangle;

typedef struct rectangle_operations {
    int (*get_height)(struct rectangle * const);
    void (*set_height)(struct rectangle * const, int);

    int (*get_width)(struct rectangle * const);
    void (*set_width)(struct rectangle * const, int);
} rectangle_operations;

extern const struct rectangle_operations * const rectangle_ns;

extern struct rectangle * (*new_rectangle)(void);
extern void (*free_rectangle)(struct rectangle *);

#endif // RECTANGLE_H
