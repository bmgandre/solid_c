#include "employee_repository.h"
#include "../entities/employee.h"
#include <stdlib.h>

static struct employee all_employees[] =
{
    { .id = 1, .name = "John", .salary = 1000. },
    { .id = 2, .name = "Paul", .salary = 900. },
    { .id = 3, .name = "George", .salary = 800. },
    { .id = 4, .name = "Ringo", .salary = 700. }
};

size_t all_employees_length() {
    return sizeof(all_employees) / sizeof(all_employees[0]);
}

struct employee* _find_by_id(int const employee_id) {
    struct employee* employee = NULL;

    for (size_t i = 0; i < all_employees_length(); i++) {
        if (all_employees[i].id == employee_id) {
            employee = employee_ns->clone(&all_employees[i]);
            break;
        }
    }

    return employee;
}

struct employee_repository* _new_employee_repository() {
    struct employee_repository * repository = (struct employee_repository *) calloc(1, sizeof(struct employee_repository));
    
    (*repository) = (struct employee_repository) {
        .find_by_id = &_find_by_id
    };

    return repository;
}

void _free_employee_repository(struct employee_repository* employee_repository) {
    free(employee_repository);
}

struct employee_repository* (*new_employee_repository)(void) = &_new_employee_repository;
void (*free_employee_repository)(struct employee_repository*) = &_free_employee_repository;
