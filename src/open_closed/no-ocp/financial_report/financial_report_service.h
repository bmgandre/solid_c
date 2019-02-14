#ifndef FINANCIAL_REPORT_SERVICE_H
#define FINANCIAL_REPORT_SERVICE_H

#include <time.h>
#include "../entities/financial_transaction.h"

typedef struct financial_report_result {
    int error_code;
    char* error_message;
    financial_transaction_list result;
} financial_report_result;

extern void (*free_financial_report_result)(struct financial_report_result *);

typedef struct financial_report_service {
    struct financial_report_result * (*get_transactions)(struct tm * begin, struct tm * end);
} financial_report_service;

#endif // FINANCIAL_REPORT_SERVICE_H
