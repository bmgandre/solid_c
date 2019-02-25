#ifndef FINANCIAL_DATA_GATEWAY_H
#define FINANCIAL_DATA_GATEWAY_H

#include "financial_transaction.h"

typedef struct financial_data_gateway {
    financial_transaction_list (*list)(void);
} financial_data_gateway;

extern struct financial_data_gateway * (*get_financial_data_gateway)(void);

#endif // FINANCIAL_DATA_GATEWAY_H
