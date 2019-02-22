#include "console_view.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define VALUE_WIDTH 13
#define DESCRIPTION_WIDTH 30

static void _print_header(struct screen_view_model const * const model) {
    (void) model;
}

static void _print_body_item(gpointer const data_item, gpointer const result) {
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

static void _print_body(financial_transaction_list const data) {
    g_list_foreach(data, &_print_body_item, NULL);
}

static void _print_footer(struct screen_view_model const * const model) {
    (void) model;
}

static void _print(struct screen_view_model const * const model) {
    _print_header(model);
    _print_body(model->data);
    _print_footer(model);
}

static struct console_view * _new_console_view() {
    struct console_view * console_view = (struct console_view *) calloc(1, sizeof(struct console_view));
    (*console_view) = (struct console_view) {
        .base = { .display = _print }
    };
    return console_view;
}

static void _free_console_view(struct console_view * console_view) {
    free(console_view);
}

struct console_view * (*new_console_view)(void) = &_new_console_view;
void (*free_console_view)(struct console_view *) = &_free_console_view;
