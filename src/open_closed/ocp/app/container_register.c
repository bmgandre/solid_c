#include "container_register.h"
#include "../ioc_container/container.h"
#include "../database/financial_data_mapper.h"
#include "../interactor/financial_report_generator.h"
#include "../screen_presenter/screen_presenter.h"
#include "../console_view/console_view.h"
#include "../colored_console_view/colored_console_view.h"

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

static void _register_screen_presenter() {
    struct resource presenter_resource = {
        .name = TYPE_FINANCIAL_REPORT_PRESENTER,
        .alloc = (alloc_func) new_screen_presenter,
        .free = (free_func) free_screen_presenter
    };
    get_container()->register_resource(presenter_resource);
}

static void _register_console_view() {
    struct resource console_resource = {
        .name = TYPE_SCREEN_VIEW,
        .alloc = (alloc_func) new_console_view,
        .free = (free_func) free_console_view
    };
    get_container()->register_resource(console_resource);
}

static void _register_colored_console_view() {
    struct resource console_resource = {
        .name = TYPE_SCREEN_VIEW,
        .alloc = (alloc_func) new_colored_console_view,
        .free = (free_func) free_colored_console_view
    };
    get_container()->register_resource(console_resource);
}

static void _register_resources() {
    _register_database_resource();
    _register_interactor_resource();
    _register_screen_presenter();
    // _register_console_view();
    _register_colored_console_view();
}

void (*register_resources)(void) = &_register_resources;
