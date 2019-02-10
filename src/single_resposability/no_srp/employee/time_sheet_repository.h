#ifndef TIME_SHEET_REPOSITORY_H
#define TIME_SHEET_REPOSITORY_H

#include "time_sheet.h"
#include <gmodule.h>

typedef struct time_sheet_repository {
    time_record_list (*list)(int const employee_id, int const year, enum month const month);
} time_sheet_repository;

extern struct time_sheet_repository * (*new_time_sheet_repository)(void);
extern void (*free_time_sheet_repository)(struct time_sheet_repository *);

#endif // TIME_SHEET_REPOSITORY_H
