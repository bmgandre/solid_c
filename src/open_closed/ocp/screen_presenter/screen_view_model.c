#include "screen_view_model.h"
#include <stdlib.h>
#include <string.h>

static struct screen_view_model * _new_screen_view_model() {
    struct screen_view_model * model = (screen_view_model *) calloc(1, sizeof(screen_view_model));
    return model;
}

static void _free_screen_view_model(struct screen_view_model * model) {
    free(model);
}

struct screen_view_model * (*new_screen_view_model)(void) = &_new_screen_view_model;
void (*free_screen_view_model)(struct screen_view_model *) = &_free_screen_view_model;

static void _set_string(char * destination, char * source) {
    if (destination) {
        free(destination);
    }

    destination = (char*) calloc(strlen(source) + 1, sizeof(char));
    strcpy(source, destination);
}

static char* _get_title(struct screen_view_model * screen_view_model) {
    return screen_view_model->title;
}

static void _set_title(struct screen_view_model * screen_view_model, char* title) {
    _set_string(screen_view_model->title, title);
}

static char* _get_date_time(struct screen_view_model * screen_view_model) {
    return screen_view_model->date_time;
}

static void _set_date_time(struct screen_view_model * screen_view_model, char* date_time) {
    _set_string(screen_view_model->date_time, date_time);
}

static struct screen_view_model_operations _screen_view_model_operations = {
    .get_title = &_get_title,
    .set_title = &_set_title,

    .get_date_time = &_get_date_time,
    .set_date_time = &_set_date_time
};

const struct screen_view_model_operations * const screen_view_model_ns = &_screen_view_model_operations;
