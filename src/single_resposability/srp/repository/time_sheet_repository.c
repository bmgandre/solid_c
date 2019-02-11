#include "time_sheet_repository.h"
#include <stdlib.h>

static struct time_record time_record_store[] = {
    { .employee_id = 1, .date_time = { .year = 2019, .month = JAN, .day = 1 }, .worked_time = 8.1 },
    { .employee_id = 1, .date_time = { .year = 2019, .month = JAN, .day = 2 }, .worked_time = 8. },
    { .employee_id = 1, .date_time = { .year = 2019, .month = JAN, .day = 3 }, .worked_time = 7.45 },
    { .employee_id = 1, .date_time = { .year = 2019, .month = JAN, .day = 4 }, .worked_time = 8.2 },
    { .employee_id = 1, .date_time = { .year = 2019, .month = JAN, .day = 5 }, .worked_time = 8. },
    { .employee_id = 2, .date_time = { .year = 2019, .month = JAN, .day = 1 }, .worked_time = 5. },
    { .employee_id = 2, .date_time = { .year = 2019, .month = JAN, .day = 2 }, .worked_time = 7.8 },
    { .employee_id = 2, .date_time = { .year = 2019, .month = JAN, .day = 3 }, .worked_time = 8.3 },
    { .employee_id = 2, .date_time = { .year = 2019, .month = JAN, .day = 4 }, .worked_time = 8. },
    { .employee_id = 2, .date_time = { .year = 2019, .month = JAN, .day = 5 }, .worked_time = 9. },
};

size_t time_record_store_length() {
    return sizeof(time_record_store) / sizeof(time_record_store[0]);
}

int time_record_key_comparer(struct time_record const * const left, struct time_record const * const right) {
    return left->employee_id == right->employee_id
        && left->date_time.year == right->date_time.year
        && left->date_time.month == right->date_time.month;
}

time_record_list list(int employee_id, int year, month month) {
    struct time_record key = {
        .employee_id = employee_id,
        .date_time = {
            .year = year,
            .month = month
        }
    };

    time_record_list list = NULL;
    for (size_t i = 0; i < time_record_store_length(); i++) {
        if (time_record_key_comparer(&key, &time_record_store[i]) == TRUE) {
            list = g_list_append(list, time_record_converter->to_gpointer(&time_record_store[i]));
        }
    }

    return list;
}

struct time_sheet_repository* _new_time_sheet_repository() {
    time_sheet_repository *time_sheet_repository = (struct time_sheet_repository *) calloc(1, sizeof(struct time_sheet_repository));
    
    (*time_sheet_repository) = (struct time_sheet_repository) {
        .list = &list
    };

    return time_sheet_repository;
}

void _free_time_sheet_repository(struct time_sheet_repository* time_sheet_repository) {
    free(time_sheet_repository);
}

struct time_sheet_repository * (*new_time_sheet_repository)(void) = &_new_time_sheet_repository;
void (*free_time_sheet_repository)(struct time_sheet_repository *) = &_free_time_sheet_repository;
