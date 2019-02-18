#include "financial_report_response.h"

static struct financial_report_response * _new_financial_report_response() {
    financial_report_response * response = (financial_report_response *) calloc(1, sizeof(financial_report_response));
    return response;
}

static void _free_financial_report_response(struct financial_report_response * response) {
    if (!response) {
        return;
    }

    free_financial_transaction_list(response->result);
    free(response);
}

struct financial_report_response * (*new_financial_report_response)(void) = &_new_financial_report_response;
void (*free_financial_report_response)(struct financial_report_response *) = &_free_financial_report_response;
