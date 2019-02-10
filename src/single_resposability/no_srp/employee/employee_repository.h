#ifndef EMPLOYEE_REPOSITORY_H
#define EMPLOYEE_REPOSITORY_H

#include "employee.h"
#include <gmodule.h>

typedef struct employee_repository {
    struct employee* (*find_by_id)(int const employee_id);
} employee_repository;

extern struct employee_repository* (*new_employee_repository)(void);
extern void (*free_employee_repository)(struct employee_repository*);

#endif // EMPLOYEE_REPOSITORY_H
