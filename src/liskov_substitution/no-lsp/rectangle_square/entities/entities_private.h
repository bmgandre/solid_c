#ifndef ENTITIES_PRIVATE_H
#define ENTITIES_PRIVATE_H

struct rectangle {
    int height;
    int width;
};

struct square {
    struct rectangle base;
};

#endif // ENTITIES_PRIVATE_H
