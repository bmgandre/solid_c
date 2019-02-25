#ifndef FINANCIAL_REPORT_REQUESTER_H
#define FINANCIAL_REPORT_REQUESTER_H

#include "financial_report_request.h"
#include "financial_report_response.h"

typedef struct financial_report_requester {
    struct financial_report_response * (*get_transactions)(struct financial_report_request const * const request);
} financial_report_requester;

#endif // FINANCIAL_REPORT_REQUESTER_H
