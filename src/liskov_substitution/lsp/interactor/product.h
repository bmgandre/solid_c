#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct product {
    long id;
    char * name;
} product;

extern struct product * (*new_product)(void);
extern void (*free_product)(struct product *);

typedef struct product_operations {
    long (*get_id)(struct product * const);
    void (*set_id)(struct product * const, long id);

    char * (*get_name)(struct product * const);
    void (*set_name)(struct product * const, char *);

    struct product * (*clone)(struct product const * const);
} product_operations;

extern const struct product_operations * const product_ns;

typedef GList * product_list;

extern void (*free_product_list)(product_list);

#endif // PRODUCT_H
