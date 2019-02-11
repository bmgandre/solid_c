#include "employee.h"
#include <stdlib.h>

struct employee* pointer_to_employee(gpointer pointer) {
    return (struct employee*) pointer;
}

gpointer employee_to_pointer(struct employee* employee) {
    return (gpointer) employee;
}

static employee_convert _employee_convert = {
    .to_employee = &pointer_to_employee,
    .to_gpointer = &employee_to_pointer
};

const struct employee_convert * const employee_converter = &_employee_convert;

void _free_employee(struct employee * employee) {
    memset(employee->name, 0, strlen(employee->name));
    free(employee->name);

    memset(employee, 0, sizeof(struct employee));
    free(employee);
}

struct employee * _new_employee() {
    struct employee * employee = (struct employee *) calloc(1, sizeof(struct employee));
    return employee;
}

struct employee * (*new_employee)(void) = &_new_employee;
void (*free_employee)(struct employee *) = &_free_employee;

void _set_name(struct employee * employee, char const * const name) {
    if (employee->name) {
        free(employee->name);
    }

    employee->name = (char*) calloc(strlen(name) + 1, sizeof(char));
    strcpy(employee->name, name);
}

char const * _get_name(struct employee * employee) {
    return employee->name;
}

void _set_id(struct employee * employee, int const id) {
    employee->id = id;
}

int _get_id(struct employee * employee) {
    return employee->id;
}

void _set_salary(struct employee * employee, double const salary) {
    employee->salary = salary;
}

double _get_salary(struct employee * employee) {
    return employee->salary;
}

struct employee * _clone(struct employee *other) {
    struct employee * employee = new_employee();
    _set_name(employee, other->name);
    _set_id(employee, other->id);
    _set_salary(employee, other->salary);

    return employee;
}

static struct employee_operations _employee_operations = {
    .get_id = &_get_id,
    .set_id = &_set_id,

    .get_name = &_get_name,
    .set_name = &_set_name,

    .get_salary = &_get_salary,
    .set_salary = &_set_salary,

    .clone = &_clone
};

const struct employee_operations * const  employee_ns = &_employee_operations;
