#ifndef FINANCIAL_TRANSACTION_REPOSITORY_H
#define FINANCIAL_TRANSACTION_REPOSITORY_H

#include <gmodule.h>
#include "../entities/financial_transaction.h"

typedef struct financial_transaction_repository {
    financial_transaction_list (*list)(void);
} financial_transaction_repository;

extern struct financial_transaction_repository* (*new_financial_transaction_repository)(void);
extern void (*free_financial_transaction_repository)(struct financial_transaction_repository *);

#endif // FINANCIAL_TRANSACTION_REPOSITORY_H