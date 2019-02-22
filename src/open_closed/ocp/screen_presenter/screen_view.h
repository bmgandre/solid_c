#ifndef SCREEN_VIEW_H
#define SCREEN_VIEW_H

#include "screen_view_model.h"

typedef struct screen_view {
    void (*display)(struct screen_view_model const * const);
} screen_view;

#endif // SCREEN_VIEW_H
