#include "screen_presenter.h"
#include "../interactor/financial_transaction.h"
#include "../ioc_container/container.h"
#include "screen_view.h"
#include <stdlib.h>

static void _display(financial_transaction_list const data) {
    struct screen_view * viewer = get_container()->get_resource(TYPE_SCREEN_VIEW);
    struct screen_view_model model = {
        .title = "Financial Report",
        .date_time = time(NULL),
        .data = data
    };

    viewer->display(&model);
}

static struct screen_presenter * _new_screen_presenter() {
    struct screen_presenter * presenter = (struct screen_presenter *) calloc(1, sizeof(screen_presenter));
    (*presenter) = (struct screen_presenter) {
        .base = { .display = &_display }
    };
    return presenter;
}

static void _free_screen_presenter(struct screen_presenter * presenter) {
    free(presenter);
}

struct screen_presenter * (*new_screen_presenter)(void) = &_new_screen_presenter;
void (*free_screen_presenter)(struct screen_presenter *) = &_free_screen_presenter;
