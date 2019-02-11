#ifndef EMPLOYEE_SERVICE_H
#define EMPLOYEE_SERVICE_H

#include "time_sheet.h"

typedef struct payment_calculation_result {
    int error_code;
    char* error_message;
    double payment_result;
} payment_calculation_result;

typedef struct report_hours_result {
    int error_code;
    char* error_message;
    double hours_result;
} report_hours_result;

typedef struct employee_service {
    struct payment_calculation_result (*calculate_pay)(int const employee_id, int const year, month const month);
    struct report_hours_result (*report_hours)(int const employee_id, int const year, month const month);
} employee_service;

extern struct employee_service* (*new_employee_service)(void);
extern void (*free_employee_service)(struct employee_service*);

#endif // EMPLOYEE_SERVICE_H
