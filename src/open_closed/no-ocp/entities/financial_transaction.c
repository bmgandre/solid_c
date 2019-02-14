#include "financial_transaction.h"
#include <stdlib.h>
#include <string.h>

long _get_id(struct financial_transaction * financial_transaction) {
    return financial_transaction->id;
}

void _set_id(struct financial_transaction * financial_transaction, long id) {
    financial_transaction->id = id;
}

void _set_date_time(struct financial_transaction * financial_transaction, time_t date_time) {
    financial_transaction->date_time = date_time;
}

time_t _get_date_time(struct financial_transaction * financial_transaction) {
    return financial_transaction->date_time;
}

double _get_value(struct financial_transaction * financial_transaction) {
    return financial_transaction->value;
}

void _set_value(struct financial_transaction * financial_transaction, double value) {
    financial_transaction->value = value;
}

char* _get_description(struct financial_transaction * financial_transaction) {
    return financial_transaction->description;
}

void _set_description(struct financial_transaction * financial_transaction, char* description) {
    if (financial_transaction->description) {
        free(financial_transaction->description);
    }

    financial_transaction->description = (char*) calloc(strlen(description) + 1, sizeof(char));
    strcpy(financial_transaction->description, description);
}

struct financial_transaction * _clone(struct financial_transaction * other) {
    struct financial_transaction * financial_transaction = new_financial_transaction();
    _set_id(financial_transaction, other->id);
    _set_date_time(financial_transaction, other->date_time);
    _set_value(financial_transaction, other->value);
    _set_description(financial_transaction, other->description);
    return financial_transaction;
}

static struct financial_transaction_operations _financial_transaction_operations = {
    .get_id = &_get_id,
    .set_id = &_set_id,

    .get_date_time = &_get_date_time,
    .set_date_time = &_set_date_time,

    .get_value = &_get_value,
    .set_value = &_set_value,

    .get_description = &_get_description,
    .set_description = &_set_description,

    .clone = &_clone
};

const struct financial_transaction_operations * const financial_transaction_ns = &_financial_transaction_operations;

void _free_financial_transaction(struct financial_transaction * financial_transaction) {
    if (!financial_transaction) {
        return;
    }

    if (financial_transaction->description) {
        memset(financial_transaction->description, 0, strlen(financial_transaction->description));
        free(financial_transaction->description);
    }

    memset(financial_transaction, 0, sizeof(struct financial_transaction));
    free(financial_transaction);
}

struct financial_transaction * _new_financial_transaction() {
    struct financial_transaction * financial_transaction = (struct financial_transaction *) calloc(1, sizeof(struct financial_transaction));
    return financial_transaction;
}

void (*free_financial_transaction)(struct financial_transaction * financial_transaction) = &_free_financial_transaction;
struct financial_transaction * (*new_financial_transaction)(void) = &_new_financial_transaction;

struct financial_transaction* _to_financial_transaction(gpointer const pointer) {
    return (struct financial_transaction *) pointer;
}

gpointer _to_gpointer(struct financial_transaction* const financial_transaction) {
    return (gpointer) financial_transaction;
}

static struct financial_transaction_convert _financial_transaction_converter = {
    .to_financial_transaction = &_to_financial_transaction,
    .to_gpointer = &_to_gpointer
};

const struct financial_transaction_convert * const financial_transaction_converter = &_financial_transaction_converter;

void _free_financial_transaction_item(gpointer data) {
    struct financial_transaction* financial_transaction = _to_financial_transaction(data);
    _free_financial_transaction(financial_transaction);
}

void _free_financial_transaction_list(financial_transaction_list list) {
    g_list_free_full(list, &_free_financial_transaction_item);
}

void (*free_financial_transaction_list)(financial_transaction_list) = &_free_financial_transaction_list;
