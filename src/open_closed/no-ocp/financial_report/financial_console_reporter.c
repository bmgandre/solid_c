#include "financial_console_reporter.h"
#include <stdlib.h>

void _print_header(financial_transaction_list data) {

}

void _print_body_item(gpointer data_item, gpointer result) {
    (void) result; // unused

    struct financial_transaction * financial_transacation = financial_transaction_converter->to_financial_transaction(data_item);
}

void _print_body(financial_transaction_list data) {
    g_list_foreach(data, &_print_body_item, NULL);
}

void _print_footer(financial_transaction_list data) {

}

void _print(financial_transaction_list data) {
    _print_header(data);
    _print_body(data);
    _print_footer(data);
}

struct financial_console_reporter * _new_financial_console_reporter(void) {
    struct financial_console_reporter * reporter = (struct financial_console_reporter *) calloc(1, sizeof(struct financial_console_reporter));
    (*reporter) = (struct financial_console_reporter) {
        .print = &_print
    };
    return reporter;
}

void _free_financial_console_reporter(struct financial_console_reporter * financial_console_reporter) {
    free(financial_console_reporter);
}

struct financial_console_reporter * (*new_financial_console_reporter)(void) = &_new_financial_console_reporter;
void (*free_financial_console_reporter)(struct financial_console_reporter *) = &_free_financial_console_reporter;
