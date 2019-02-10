#include <stdio.h>
#include "entities/date_time.h"
#include "payment/payment_service.h"
#include "time_sheet/time_sheet_service.h"

int main() {
    payment_service* payment_service = new_payment_service();
    time_sheet_service* time_sheet_service = new_time_sheet_service();

    int employee_id = 1;
    int year = 2019;
    month month = JAN;

    struct payment_calculation_result pay_result = payment_service->calculate_pay(employee_id, year, month);
    struct report_hours_result hours_result = time_sheet_service->report_hours(employee_id, year, month);

    free_payment_service(payment_service);

    printf("Employee: %d\n", employee_id);
    printf("|- payment: %f\n", pay_result.payment_result);
    //printf("|- hours..: %f\n", hours_result.hours_result);

    return 0;
}
