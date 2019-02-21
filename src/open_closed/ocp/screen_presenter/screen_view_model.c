#include "screen_view_model.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char* _get_title(struct screen_view_model * screen_view_model) {
    return screen_view_model->title;
}

static time_t _get_date_time(struct screen_view_model * screen_view_model) {
    return screen_view_model->date_time;
}

static financial_transaction_list _get_transaction_list(struct screen_view_model * screen_view_mode) {
    return screen_view_mode->data;
}

static const struct screen_view_model_operations _screen_view_model_operations = {
    .get_title = &_get_title,
    .get_date_time = &_get_date_time,
    .get_transaction_list = &_get_transaction_list
};

const struct screen_view_model_operations * const screen_view_model_ns = &_screen_view_model_operations;
