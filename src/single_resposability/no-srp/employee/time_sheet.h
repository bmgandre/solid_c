#ifndef TIME_SHEET_H
#define TIME_SHEET_H

#include <time.h>
#include <gmodule.h>
#include "employee.h"

typedef enum month {
    JAN = 0, FEB, MAR, APR, MAY, JUN,
    JUL, AUG, SEP, OCT, NOV, DEC
} month;

typedef struct date_time {
    int year;
    month month;
    int day;
} date_time;

typedef struct time_record {
    int employee_id;
    date_time date_time;
    double worked_time;
} time_record;

typedef struct time_record_convert {
    struct time_record* (*to_time_record)(gpointer const);
    gpointer (*to_gpointer)(struct time_record * const);
} time_record_convert;

extern const struct time_record_convert * const time_record_converter;

typedef GList* time_record_list;

#endif // TIME_SHEET_H
