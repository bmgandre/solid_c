#include "container.h"
#include <gmodule.h>
#include <stdlib.h>

typedef struct resource_private {
    struct resource base;
    void * resource_ptr;
} resource_private;

static GHashTable * _data_table = NULL;

static void _register_resource(struct resource resource) {
    resource_private * rp = (resource_private *) calloc(1, sizeof(resource_private));
    (*rp) = (resource_private) {
        .base = resource
    };
    g_hash_table_insert(_data_table, GINT_TO_POINTER(resource.name), rp);
}

static void * _get_resource(typename name) {
    resource_private * rp = (resource_private *) g_hash_table_lookup(_data_table, GINT_TO_POINTER(name));
    if (rp) {
        if (!rp->resource_ptr) {
            rp->resource_ptr = rp->base.alloc();
        }

        return rp->resource_ptr;
    }
    return NULL;
}

static void _free_resource(typename name) {
    resource_private * rp = (resource_private *) g_hash_table_lookup(_data_table, GINT_TO_POINTER(name));
    if (rp) {
        if (!rp->resource_ptr) {
            rp->base.free(rp->resource_ptr);
        }
    }
}

static const struct container _container = {
    .register_resource = &_register_resource,
    .get_resource = &_get_resource,
    .free_resource = &_free_resource
};

static void _init_container() {
    if (_data_table == NULL) {
        _data_table = g_hash_table_new_full(&g_direct_hash, &g_direct_equal, NULL, NULL);
    }
}

static struct container const * _get_container() {
    _init_container();
    return &_container;
}

struct container const * (*get_container)(void) = &_get_container;

static gboolean _free_container_item(gpointer key, gpointer value, gpointer user_data) {
    (void) key; // unused
    (void) user_data; // unused

    resource_private * rp = (resource_private *) value;
    if (rp->base.free && rp->resource_ptr) {
        rp->base.free(rp->resource_ptr);
    }
    free(rp);

    return TRUE;
}

static void _free_container() {
    g_hash_table_foreach_remove(_data_table, _free_container_item, NULL);
    g_hash_table_destroy(_data_table);
}

void (*free_container)(void) = &_free_container;
