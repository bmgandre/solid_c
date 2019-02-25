#ifndef FINANCIAL_REPORT_GENERATOR_H
#define FINANCIAL_REPORT_GENERATOR_H

#include "financial_report_requester.h"
#include "financial_report_request.h"
#include "financial_report_response.h"

typedef struct financial_report_generator {
    struct financial_report_requester base;
} financial_report_generator;

extern struct financial_report_generator * (*new_financial_report_generator)(void);
extern void (*free_financial_report_generator)(struct financial_report_generator*);

#endif // FINANCIAL_REPORT_GENERATOR_H
