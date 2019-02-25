#include "console_view.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define VALUE_WIDTH (13)
#define DESCRIPTION_WIDTH (30)
#define DATE_WIDTH (20)
#define LINE_WIDTH (VALUE_WIDTH + DESCRIPTION_WIDTH + DATE_WIDTH + 5)

static void _print_title_centered(struct screen_view_model const * const model) {
    printf("%*s\n\n", (int)(LINE_WIDTH + strlen(model->title)) / 2, model->title);
}

static void _print_header(struct screen_view_model const * const model) {
    _print_title_centered(model);
}

static void _set_formatted_date(struct financial_transaction const * const financial_transaction, char * const date_buffer) {
    strftime(date_buffer, sizeof(char) * DATE_WIDTH, "%F %T", localtime(&financial_transaction->date_time));
}

static void _print_body_item_positive(struct financial_transaction const * const financial_transaction) {
    char date_buffer[DATE_WIDTH];
    _set_formatted_date(financial_transaction, date_buffer);

    printf("%s | %-*.30s | %*.2f\n",
           date_buffer,
           DESCRIPTION_WIDTH, financial_transaction->description,
           VALUE_WIDTH, financial_transaction->value);
}

static void _print_body_item_negative(struct financial_transaction const * const financial_transaction) {
    char formatted_number_buffer[VALUE_WIDTH];
    sprintf(formatted_number_buffer, "(%.2f)", fabs(financial_transaction->value));

    char date_buffer[DATE_WIDTH];
    _set_formatted_date(financial_transaction, date_buffer);

    printf("%s | %-*.30s | %*s\n",
           date_buffer,
           DESCRIPTION_WIDTH, financial_transaction->description,
           VALUE_WIDTH, formatted_number_buffer);
}

static void _print_body_item(gpointer const data_item, gpointer const result) {
    (void) result; // unused

    struct financial_transaction * financial_transaction = financial_transaction_converter->to_financial_transaction(data_item);

    if (financial_transaction->value >= 0) {
        _print_body_item_positive(financial_transaction);
    } else {
        _print_body_item_negative(financial_transaction);
    }
}

static void _print_body(financial_transaction_list const data) {
    g_list_foreach(data, &_print_body_item, NULL);
}

static void _sum_transactions(gpointer const data_item, gpointer const result) {
    struct financial_transaction * financial_transaction = financial_transaction_converter->to_financial_transaction(data_item);
    double * sum = result;
    *sum = *sum + financial_transaction->value;
}

static void _print_footer_line_divisor() {
    char line_divisor_buffer[LINE_WIDTH + 1];
    memset(line_divisor_buffer, '-', LINE_WIDTH);
    line_divisor_buffer[LINE_WIDTH] = '\0';
    printf("%s\n", line_divisor_buffer);
}

static void _print_footer_total_positive(double total) {
    printf("%*s   %*.30s | %*.2f\n",
           DATE_WIDTH - 1, "",
           DESCRIPTION_WIDTH, "Total",
           VALUE_WIDTH, total);
}

static void _print_footer_total_negative(double total) {
    char formatted_number_buffer[VALUE_WIDTH];
    sprintf(formatted_number_buffer, "(%.2f)", fabs(total));

    printf("%*s   %*.30s | %*s\n",
           DATE_WIDTH - 1, "",
           DESCRIPTION_WIDTH, "Total",
           VALUE_WIDTH, formatted_number_buffer);
}

static void _print_footer_generated(struct screen_view_model const * const model) {
    char date_buffer[DATE_WIDTH];
    strftime(date_buffer, sizeof(date_buffer), "%F %T", localtime(&model->date_time));
    printf("\n\n%*s\n", LINE_WIDTH, date_buffer);
}

static void _print_footer(struct screen_view_model const * const model) {
    double result = .0;
    g_list_foreach(model->data, &_sum_transactions, &result);

    _print_footer_line_divisor();
    if (result >= 0) {
        _print_footer_total_positive(result);
    } else {
        _print_footer_total_negative(result);
    }

    _print_footer_generated(model);
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
