#ifndef SCREEN_PRESENTER_H
#define SCREEN_PRESENTER_H

#include "../controller/financial_report_presenter.h"

typedef struct screen_presenter {
    financial_report_presenter base;
} screen_presenter;

extern struct screen_presenter * (*new_screen_presenter)(void);
extern void (*free_screen_presenter)(struct screen_presenter *);

#endif // SCREEN_PRESENTER_H
