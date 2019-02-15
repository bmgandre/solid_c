#ifndef CONSOLE_REPORTER_H
#define CONSOLE_REPORTER_H

#include "../entities/financial_transaction.h"

typedef struct financial_console_reporter {
    void (*print)(financial_transaction_list data);
} financial_console_reporter;

extern struct financial_console_reporter * (*new_financial_console_reporter)(void);
extern void (*free_financial_console_reporter)(struct financial_console_reporter *);

#endif // CONSOLE_REPORTER_H
