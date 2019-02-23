#ifndef COLORED_CONSOLE_VIEW_H
#define COLORED_CONSOLE_VIEW_H

#include "../screen_presenter/screen_view.h"

typedef struct colored_console_view {
    screen_view base;
} colored_console_view;

extern struct colored_console_view * (*new_colored_console_view)(void);
extern void (*free_colored_console_view)(struct colored_console_view *);

#endif // COLORED_CONSOLE_VIEW_H
