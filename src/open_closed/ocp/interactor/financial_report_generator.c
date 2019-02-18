#include "financial_report_generator.h"
#include "financial_data_gateway.h"

static struct financial_report_response * _get_transactions(struct financial_report_request * request) {
    struct financial_report_response * result = new_financial_report_response();

    time_t begin_date = mktime(request->begin_date_time);
    if (begin_date == -1) {
        (*result) = (struct financial_report_response) {
            .error_code = -1,
            .error_message = "Invalid begin date time parameter"
        };

        return result;
    }

    time_t end_date = mktime(request->end_date_time);
    if (end_date == -1) {
        (*result) = (struct financial_report_response) {
            .error_code = -2,
            .error_message = "Invalid end date time parameter"
        };

        return result;
    }

    struct financial_data_gateway * repository = get_financial_data_gateway();
    financial_transaction_list all_transaction_list = repository->list();

    GList* transaction_list = NULL;
    for (GList * list_item = all_transaction_list; list_item != NULL; list_item = g_list_next(list_item)) {
        struct financial_transaction * transaction = financial_transaction_converter->to_financial_transaction(list_item->data);
        if (transaction->date_time >= begin_date && transaction->date_time <= end_date) {
            transaction_list = g_list_append(transaction_list, transaction);
        }
    }

    g_list_free(all_transaction_list);
    result->result = transaction_list;

    return result;
}

static struct financial_report_generator * _new_financial_report_generator() {
    struct financial_report_generator * report = (struct financial_report_generator *) calloc(1, sizeof(financial_report_generator));
    (*report) = (struct financial_report_generator) {
        .base = { .get_transactions = &_get_transactions }
    };

    return report;
}

static void _free_financial_report_generator(struct financial_report_generator * financial_report_generator) {
    free(financial_report_generator);
}

struct financial_report_generator * (*new_financial_report_generator)(void) = &_new_financial_report_generator;
void (*free_financial_report_generator)(struct financial_report_generator*) = &_free_financial_report_generator;
