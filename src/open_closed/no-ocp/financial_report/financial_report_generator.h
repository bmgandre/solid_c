#ifndef FINANCIAL_REPORT_GENERATOR_H
#define FINANCIAL_REPORT_GENERATOR_H

#include <time.h>
#include "../entities/financial_transaction.h"

typedef struct financial_report_result {
    int error_code;
    char* error_message;
    financial_transaction_list result;
} financial_report_result;

extern void (*free_financial_report_result)(struct financial_report_result *);

typedef struct financial_report_generator {
    struct financial_report_result * (*get_transactions)(struct tm * begin, struct tm * end);
} financial_report_generator;

#endif // FINANCIAL_REPORT_GENERATOR_H
