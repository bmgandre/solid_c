#ifndef TIME_SHEET_SERVICE_H
#define TIME_SHEET_SERVICE_H

#include "../entities/time_sheet.h"

typedef struct report_hours_result {
    int error_code;
    char* error_message;
    double hours_result;
} report_hours_result;

typedef struct time_sheet_service {
    struct report_hours_result (*report_hours)(int const employee_id, int const year, month const month);
} time_sheet_service;

extern struct time_sheet_service * (*new_time_sheet_service)(void);
extern void (*free_time_sheet_service)(struct time_sheet_service *);

#endif // TIME_SHEET_SERVICE_H
