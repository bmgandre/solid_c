#include "financial_report_request.h"
#include <stdlib.h>

static struct financial_report_request * _new_financial_report_request() {
    financial_report_request * request = (financial_report_request *) calloc(1, sizeof(financial_report_request));
    return request;
}

static void _free_financial_report_request(struct financial_report_request * request) {
    free(request);
}

struct financial_report_request * (*new_financial_report_request)(void) = &_new_financial_report_request;
void (*free_financial_report_request)(struct financial_report_request *) = &_free_financial_report_request;
