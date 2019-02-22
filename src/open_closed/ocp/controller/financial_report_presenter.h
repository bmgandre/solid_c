#ifndef FINANCIAL_REPORT_PRESENTER_H
#define FINANCIAL_REPORT_PRESENTER_H

#include "../interactor/financial_transaction.h"

typedef struct financial_report_presenter {
    void (*display)(financial_transaction_list const data);
} financial_report_presenter;

#endif // FINANCIAL_REPORT_PRESENTER_H
