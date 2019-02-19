#ifndef FINANCIAL_REPORT_PRESENTER_H
#define FINANCIAL_REPORT_PRESENTER_H

#include "../interactor/financial_transaction.h"

typedef struct financial_report_presenter {
    void (*display)(financial_transaction_list data);
} financial_report_presenter;

extern struct financial_report_presenter * (*get_financial_report_presenter)(void);

#endif // FINANCIAL_REPORT_PRESENTER_H
