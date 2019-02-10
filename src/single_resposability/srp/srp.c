#include <stdio.h>
#include "entities/date_time.h"
#include "payment/payment_service.h"

int main() {
    employee_service* employee_service = new_employee_service();

    int employee_id = 1;
    int year = 2019;
    month month = JAN;

    struct payment_calculation_result pay_result = employee_service->calculate_pay(employee_id, year, month);
    struct report_hours_result hours_result = employee_service->report_hours(employee_id, year, month);

    free_employee_service(employee_service);

    printf("Employee: %d\n", employee_id);
    printf("|- payment: %f\n", pay_result.payment_result);
    printf("|- hours..: %f\n", hours_result.hours_result);

    return 0;
}
