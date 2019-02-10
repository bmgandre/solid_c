#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <gmodule.h>

typedef struct employee {
    int id;
    char* name;
    double salary;
} employee;

typedef struct employee_operations {
    void (*set_name)(struct employee * employee, char const * const name);
    char const * (*get_name)(struct employee * employee);

    void (*set_id)(struct employee * employee, int const id);
    int (*get_id)(struct employee * employee);

    void (*set_salary)(struct employee * employee, double const salary);
    double (*get_salary)(struct employee * employee);

    struct employee * (*clone)(struct employee *);
} employee_operations;

extern const struct employee_operations * const  employee_ns;

extern void (*free_employee)(struct employee *);
extern struct employee * (*new_employee)(void);

typedef struct employee_convert {
    struct employee* (*to_employee)(gpointer const);
    gpointer (*to_gpointer)(struct employee* const);
} employee_convert;

extern const struct employee_convert * const employee_converter;

typedef GList* employee_list;

#endif // EMPLOYEE_H
