#ifndef SCREEN_VIEW_MODEL_H
#define SCREEN_VIEW_MODEL_H

typedef struct screen_view_model {
    char * title;
    char * date_time;
} screen_view_model;

typedef struct screen_view_model_operations {
    char* (*get_title)(struct screen_view_model * screen_view_model);
    void (*set_title)(struct screen_view_model * screen_view_model, char* title);

    char* (*get_date_time)(struct screen_view_model * screen_view_model);
    void (*set_date_time)(struct screen_view_model * screen_view_model, char* date_time);
} screen_view_model_operations;

extern const struct screen_view_model_operations * const screen_view_model_ns;

extern struct screen_view_model * (*new_screen_view_model)(void);
extern void (*free_screen_view_model)(struct screen_view_model *);

#endif // SCREEN_VIEW_MODEL_H
