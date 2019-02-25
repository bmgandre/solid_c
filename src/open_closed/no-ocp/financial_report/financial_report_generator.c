#include "financial_report_generator.h"
#include "../repository/financial_transaction_repository.h"
#include <stdlib.h>

static struct financial_report_result * _new_financial_report_result() {
    struct financial_report_result * result = (struct financial_report_result *) calloc(1, sizeof(financial_report_result));
    return result;
}

static void _free_financial_report_result(struct financial_report_result * financial_report_result) {
    if (!financial_report_result) {
        return;
    }

    free_financial_transaction_list(financial_report_result->result);
    free(financial_report_result);
}

void (*free_financial_report_result)(struct financial_report_result *) = &_free_financial_report_result;

static struct financial_report_result * _get_transactions(struct tm * begin, struct tm * end) {
    struct financial_report_result * result = _new_financial_report_result();

    time_t begin_date = mktime(begin);
    if (begin_date == -1) {
        (*result) = (struct financial_report_result) {
            .error_code = -1,
            .error_message = "Invalid begin date time parameter"
        };

        return result;
    }

    time_t end_date = mktime(end);
    if (end_date == -1) {
        (*result) = (struct financial_report_result) {
            .error_code = -2,
            .error_message = "Invalid end date time parameter"
        };

        return result;
    }

    struct financial_transaction_repository * repository = new_financial_transaction_repository();
    financial_transaction_list all_transaction_list = repository->list();
    free_financial_transaction_repository(repository);

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
        .get_transactions = &_get_transactions
    };

    return report;
}

static void _free_financial_report_generator(struct financial_report_generator * financial_report_generator) {
    free(financial_report_generator);
}

struct financial_report_generator * (*new_financial_report_generator)(void) = &_new_financial_report_generator;
void (*free_financial_report_generator)(struct financial_report_generator*) = &_free_financial_report_generator;
