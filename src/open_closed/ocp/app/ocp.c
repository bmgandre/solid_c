#include "../ioc_container/container.h"
#include "../controller/financial_report_controller.h"
#include "container_register.h"

int main() {
    struct tm start_date = {
        .tm_year = 119, .tm_mon = 0, .tm_mday = 1,
        .tm_hour = 0,   .tm_min = 0, .tm_sec = 0
    };
    struct tm end_date = {
        .tm_year = 119, .tm_mon = 0, .tm_mday = 31,
        .tm_hour = 0,   .tm_min = 0, .tm_sec = 0
    };

    register_resources();

    struct financial_report_controller * controller = new_financial_report_controller();
    controller->generate_report(&start_date, &end_date);
    free_financial_report_controller(controller);

    free_container();
    return 0;
}
