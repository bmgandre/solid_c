#ifndef PAYMENT_SERVICE_H
#define PAYMENT_SERVICE_H

#include "../entities/time_sheet.h"

typedef struct payment_calculation_result {
    int error_code;
    char* error_message;
    double payment_result;
} payment_calculation_result;

typedef struct payment_service {
    struct payment_calculation_result (*calculate_pay)(int const employee_id, int const year, month const month);
} payment_service;

extern struct payment_service* (*new_payment_service)(void);
extern void (*free_payment_service)(struct payment_service*);

#endif // PAYMENT_SERVICE_H
