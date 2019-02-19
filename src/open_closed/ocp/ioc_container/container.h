#ifndef CONTAINER_H
#define CONTAINER_H

typedef void * (*alloc_func)(void);
typedef void (*free_func)(const void *);

typedef enum typename {
    TYPE_NONE,
    TYPE_FINANCIAL_DATA_GATEWAY
} typename;

typedef struct resource {
    typename name;
    alloc_func alloc;
    free_func free;
} resource;

typedef struct container {
    void (*register_resource)(struct resource resource);
    void* (*get_resource)(typename name);
    void (*free_resource)(typename name);
} container;

extern struct container * (*get_container)(void);
extern void (*free_container)(void);

#endif // CONTAINER_H
