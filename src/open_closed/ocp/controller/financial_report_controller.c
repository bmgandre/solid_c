#include "financial_report_controller.h"
#include "financial_report_presenter.h"
#include "../ioc_container/container.h"
#include "../interactor/financial_report_requester.h"
#include "../interactor/financial_report_request.h"
#include "../interactor/financial_report_response.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static void _generate_report(struct tm * const begin, struct tm * const end) {
    struct financial_report_requester * report_requester = (struct financial_report_requester *) get_container()->get_resource(TYPE_FINANCIAL_REPORT_REQUESTER);
    struct financial_report_request request = {
        .begin_date_time = begin,
        .end_date_time = end
    };
    struct financial_report_response * response = report_requester->get_transactions(&request);

    struct financial_report_presenter * presenter = (struct financial_report_presenter *) get_container()->get_resource(TYPE_FINANCIAL_REPORT_PRESENTER);
    presenter->display(response->result);
    get_container()->free_resource(TYPE_FINANCIAL_REPORT_PRESENTER);

    free_financial_report_response(response);
    get_container()->free_resource(TYPE_FINANCIAL_REPORT_REQUESTER);
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
