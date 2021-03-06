#ifndef FINANCIAL_REPORT_RESPONSE_H
#define FINANCIAL_REPORT_RESPONSE_H

#include "financial_transaction.h"

typedef struct financial_report_response {
    int const error_code;
    char const * const error_message;
    financial_transaction_list const result;
} financial_report_response;

extern struct financial_report_response * (*new_financial_report_response)(void);
extern void (*free_financial_report_response)(struct financial_report_response *);

#endif // FINANCIAL_REPORT_RESPONSE_H
