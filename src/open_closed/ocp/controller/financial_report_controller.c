#include "financial_report_controller.h"
#include <stdlib.h>
#include <time.h>

static void _generate_report(struct tm * begin, struct tm * end) {
    (void) begin;
    (void) end;
}

struct financial_report_controller * _new_financial_report_controller() {
    financial_report_controller * controller = (financial_report_controller *) calloc(1, sizeof(financial_report_controller));
    (*controller) = (financial_report_controller) {
        .generate_report = &_generate_report
    };
    return controller;
}

void _free_financial_report_controller(struct financial_report_controller * controller) {
    if (!controller) {
        return;
    }

    free(controller);
}

struct financial_report_controller * (*new_financial_report_controller)(void) = &_new_financial_report_controller;
void (*free_financial_report_controller)(struct financial_report_controller *) = &_free_financial_report_controller;
