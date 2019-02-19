#include "container_register.h"
#include "../ioc_container/container.h"
#include "../database/financial_data_mapper.h"
#include "../interactor/financial_report_generator.h"

static void _register_interactor_resource() {
    struct resource interactor_resource = {
        .name = TYPE_FINANCIAL_REPORT_REQUESTER,
        .alloc = (alloc_func) new_financial_report_generator,
        .free = (free_func) free_financial_report_generator
    };
    get_container()->register_resource(interactor_resource);
}

static void _register_database_resource() {
    struct resource database_resource = {
        .name = TYPE_FINANCIAL_DATA_GATEWAY,
        .alloc = (alloc_func) new_financial_data_mapper,
        .free = (free_func) free_financial_data_mapper
    };
    get_container()->register_resource(database_resource);
}

static void _register_resources() {
    _register_database_resource();
    _register_interactor_resource();
}

void (*register_resources)(void) = &_register_resources;