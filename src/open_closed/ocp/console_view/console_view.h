#ifndef CONSOLE_VIEW_H
#define CONSOLE_VIEW_H

#include "../screen_presenter/screen_view.h"

typedef struct console_view {
    screen_view base;
} console_view;

extern struct console_view * (*new_console_view)(void);
extern void (*free_console_view)(struct console_view *);

#endif // CONSOLE_VIEW_H
