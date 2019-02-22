#ifndef FINANCIAL_TRANSACTION_H
#define FINANCIAL_TRANSACTION_H

#include <time.h>
#include <gmodule.h>

typedef struct financial_transaction {
    long id;
    time_t date_time;
    double value;
    char* description;
} financial_transaction;

typedef struct financial_transaction_operations {
    long (*get_id)(struct financial_transaction * const financial_transaction);
    void (*set_id)(struct financial_transaction * const financial_transaction, long id);

    void (*set_date_time)(struct financial_transaction * const financial_transaction, time_t date_time);
    time_t (*get_date_time)(struct financial_transaction * const financial_transaction);

    double (*get_value)(struct financial_transaction * const financial_transaction);
    void (*set_value)(struct financial_transaction * const financial_transaction, double value);

    char const * (*get_description)(struct financial_transaction * const financial_transaction);
    void (*set_description)(struct financial_transaction * const financial_transaction, char * const description);

    struct financial_transaction * (*clone)(struct financial_transaction const * const);
} financial_transaction_operations;

extern const struct financial_transaction_operations * const  financial_transaction_ns;

extern void (*free_financial_transaction)(struct financial_transaction *);
extern struct financial_transaction * (*new_financial_transaction)(void);

typedef struct financial_transaction_convert {
    struct financial_transaction* (*to_financial_transaction)(gpointer const);
    gpointer (*to_gpointer)(struct financial_transaction* const);
} financial_transaction_convert;

extern const struct financial_transaction_convert * const financial_transaction_converter;

typedef GList * financial_transaction_list;

extern void (*free_financial_transaction_list)(financial_transaction_list);

#endif // FINANCIAL_TRANSACTION_H
