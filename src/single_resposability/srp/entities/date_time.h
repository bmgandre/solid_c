#ifndef DATE_TIME_H
#define DATE_TIME_H

typedef enum month {
    JAN = 0, FEB, MAR, APR, MAY, JUN,
    JUL, AUG, SEP, OCT, NOV, DEC
} month;

typedef struct date_time {
    int year;
    month month;
    int day;
} date_time;

#endif // DATE_TIME_H
