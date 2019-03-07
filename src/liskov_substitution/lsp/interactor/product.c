#include "product.h"

struct product * _new_product(void) {
    struct
}

void _free_product(struct product *) {

}

struct product * (*new_product)(void) = &_new_product;
void (*free_product)(struct product *) = &_free_product;
