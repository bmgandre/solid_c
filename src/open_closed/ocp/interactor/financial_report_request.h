#ifndef FINANCIAL_REPORT_REQUEST_H
#define FINANCIAL_REPORT_REQUEST_H

typedef struct financial_report_request {
    struct tm * begin_date_time;
    struct tm * end_date_time;
} financial_report_request;

extern struct financial_report_request * (*new_financial_report_request)(void);
extern void (*free_financial_report_request)(struct financial_report_request *);

#endif // FINANCIAL_REPORT_REQUEST_H
