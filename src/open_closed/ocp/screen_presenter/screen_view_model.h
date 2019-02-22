#ifndef SCREEN_VIEW_MODEL_H
#define SCREEN_VIEW_MODEL_H

#include <time.h>
#include "../interactor/financial_transaction.h"

typedef struct screen_view_model {
    char const * const title;
    time_t const date_time;
    financial_transaction_list const data;
} screen_view_model;

typedef struct screen_view_model_operations {
    char const * (*get_title)(struct screen_view_model * const screen_view_model);
    time_t (*get_date_time)(struct screen_view_model * const screen_view_model);
    financial_transaction_list (*get_transaction_list)(struct screen_view_model * const screen_view_model);
} screen_view_model_operations;

extern const struct screen_view_model_operations * const screen_view_model_ns;

#endif // SCREEN_VIEW_MODEL_H
