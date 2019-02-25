#ifndef FINANCIAL_COLORED_CONSOLE_REPORTER_H
#define FINANCIAL_COLORED_CONSOLE_REPORTER_H

#include "../entities/financial_transaction.h"

typedef struct financial_colored_console_reporter {
    void (*print)(financial_transaction_list data);
} financial_colored_console_reporter;

extern struct financial_colored_console_reporter * (*new_financial_colored_console_reporter)(void);
extern void (*free_financial_colored_console_reporter)(struct financial_colored_console_reporter *);

#endif // FINANCIAL_COLORED_CONSOLE_REPORTER_H
