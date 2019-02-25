#ifndef FINANCIAL_REPORT_CONTROLLER_H
#define FINANCIAL_REPORT_CONTROLLER_H

#include <time.h>

typedef struct financial_report_controller {
    void (*generate_report)(struct tm * const begin, struct tm * const end);
} financial_report_controller;

extern struct financial_report_controller * (*new_financial_report_controller)(void);
extern void (*free_financial_report_controller)(struct financial_report_controller *);

#endif // FINANCIAL_REPORT_CONTROLLER_H
