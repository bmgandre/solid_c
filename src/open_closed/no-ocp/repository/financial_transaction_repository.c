#include "financial_transaction_repository.h"
#include "../entities/financial_transaction.h"
#include <stdlib.h>
#include <time.h>

struct financial_transaction financial_transaction_store[] =  {
    { .id = 1, .date_time = 1546340400, .value = 10., .description = "Printer maintainence" },
    { .id = 2, .date_time = 1546351200, .value = 120., .description = "Keyboard PC101" },
    { .id = 3, .date_time = 1546423200, .value = 1000., .description = "GPU board" },
    { .id = 4, .date_time = 1546459200, .value = 500., .description = "Software X license" },
};

size_t financial_transaction_store_length() {
    return sizeof(financial_transaction_store) / sizeof(financial_transaction_store[0]);
}

financial_transaction_list _list() {
    
    financial_transaction_list list = NULL;
    for (size_t i = 0; i < financial_transaction_store_length(); i++) {
        list = g_list_append(list, financial_transaction_converter->to_gpointer(&financial_transaction_store[i]));
    }

    return list;
}

struct financial_transaction_repository* _new_financial_transaction_repository(void) {
    struct financial_transaction_repository * repository = (struct financial_transaction_repository *) calloc(1, sizeof(struct financial_transaction_repository));
    (*repository) = (struct financial_transaction_repository) {
        .list = &_list
    };
    return repository;
}

void _free_financial_transaction_repository(struct financial_transaction_repository * financial_transaction_repository) {
    free(financial_transaction_repository);
}

struct financial_transaction_repository* (*new_financial_transaction_repository)(void) = &_new_financial_transaction_repository;
void (*free_financial_transaction_repository)(struct financial_transaction_repository *) = &_free_financial_transaction_repository;