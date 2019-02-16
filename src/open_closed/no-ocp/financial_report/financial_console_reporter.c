#include "financial_console_reporter.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define VALUE_WIDTH 13
#define DESCRIPTION_WIDTH 30

static void _print_header(financial_transaction_list data) {
    (void) data;
}

static void _print_body_item(gpointer data_item, gpointer result) {
    (void) result; // unused

    struct financial_transaction * financial_transaction = financial_transaction_converter->to_financial_transaction(data_item);

    char date_buffer[21];
    strftime(date_buffer, sizeof(date_buffer), "%F %T", localtime(&financial_transaction->date_time));

    if (financial_transaction->value >= 0) {
        printf("%s | %*.30s | %*.2f\n",
               date_buffer,
               DESCRIPTION_WIDTH, financial_transaction->description,
               VALUE_WIDTH, financial_transaction->value);
    } else {
        printf("%s | %*.30s | (%*.2f)\n",
               date_buffer,
               DESCRIPTION_WIDTH, financial_transaction->description,
               VALUE_WIDTH - 2, fabs(financial_transaction->value));
    }
}

static void _print_body(financial_transaction_list data) {
    g_list_foreach(data, &_print_body_item, NULL);
}

static void _print_footer(financial_transaction_list data) {
    (void) data;
}

static void _print(financial_transaction_list data) {
    _print_header(data);
    _print_body(data);
    _print_footer(data);
}

static struct financial_console_reporter * _new_financial_console_reporter(void) {
    struct financial_console_reporter * reporter = (struct financial_console_reporter *) calloc(1, sizeof(struct financial_console_reporter));
    (*reporter) = (struct financial_console_reporter) {
        .print = &_print
    };
    return reporter;
}

static void _free_financial_console_reporter(struct financial_console_reporter * financial_console_reporter) {
    free(financial_console_reporter);
}

struct financial_console_reporter * (*new_financial_console_reporter)(void) = &_new_financial_console_reporter;
void (*free_financial_console_reporter)(struct financial_console_reporter *) = &_free_financial_console_reporter;
