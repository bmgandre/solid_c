#ifndef FINANCIAL_DATA_MAPPER_H
#define FINANCIAL_DATA_MAPPER_H

#include "../interactor/financial_data_gateway.h"
#include "../interactor/financial_transaction.h"

typedef struct financial_data_mapper {
    financial_data_gateway base;
} financial_data_mapper;

extern struct financial_data_mapper* (*new_financial_data_mapper)(void);
extern void (*free_financial_data_mapper)(struct financial_data_mapper *);

#endif // FINANCIAL_DATA_MAPPER_H
