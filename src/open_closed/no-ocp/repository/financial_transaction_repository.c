#include "financial_transaction_repository.h"
#include "../entities/financial_transaction.h"
#include <stdlib.h>
#include <time.h>

static struct financial_transaction financial_transaction_store[] =  {
    { .id = 1, .date_time = 1546340400, .value = 10., .description = "Printer card" },
    { .id = 2, .date_time = 1546351200, .value = 120., .description = "Keyboard PC101" },
    { .id = 3, .date_time = 1546423200, .value = 1000., .description = "GPU board" },
    { .id = 4, .date_time = 1546459200, .value = 500., .description = "Software X license" },
    { .id = 5, .date_time = 1546589200, .value = -300, .description = "Cabinet" }
};

static size_t _financial_transaction_store_length() {
    return sizeof(financial_transaction_store) / sizeof(financial_transaction_store[0]);
}

static financial_transaction_list _list() {
    financial_transaction_list list = NULL;
    for (size_t i = 0; i < _financial_transaction_store_length(); i++) {
        struct financial_transaction * item = financial_transaction_ns->clone(&financial_transaction_store[i]);
        list = g_list_append(list, financial_transaction_converter->to_gpointer(item));
    }

    return list;
}

static struct financial_transaction_repository* _new_financial_transaction_repository(void) {
    struct financial_transaction_repository * repository = (struct financial_transaction_repository *) calloc(1, sizeof(struct financial_transaction_repository));
    (*repository) = (struct financial_transaction_repository) {
        .list = &_list
    };
    return repository;
}

static void _free_financial_transaction_repository(struct financial_transaction_repository * financial_transaction_repository) {
    free(financial_transaction_repository);
}

struct financial_transaction_repository* (*new_financial_transaction_repository)(void) = &_new_financial_transaction_repository;
void (*free_financial_transaction_repository)(struct financial_transaction_repository *) = &_free_financial_transaction_repository;
