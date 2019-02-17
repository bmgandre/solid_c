#include "../financial_report/financial_report_generator.h"
#include "../financial_report/financial_console_reporter.h"
#include "../financial_report/financial_colored_console_reporter.h"
#include <stdio.h>

typedef enum report_type {
    BLACK_WHITE,
    COLORED
} report_type;

static report_type get_report_type_from_user(void);

int main() {
    struct financial_report_generator * financial_report_generator = new_financial_report_generator();

    struct tm start_date = {
        .tm_year = 119, .tm_mon = 0, .tm_mday = 1,
        .tm_hour = 0,   .tm_min = 0, .tm_sec = 0
    };
    struct tm end_date = {
        .tm_year = 119, .tm_mon = 0, .tm_mday = 31,
        .tm_hour = 0,   .tm_min = 0, .tm_sec = 0
    };

    struct financial_report_result * financial_report_result = financial_report_generator->get_transactions(&start_date, &end_date);

    report_type report_type = get_report_type_from_user();

    if (report_type == COLORED) {
        struct financial_colored_console_reporter * colored_reporter = new_financial_colored_console_reporter();
        colored_reporter->print(financial_report_result->result);
        free_financial_colored_console_reporter(colored_reporter);
    } else {
        struct financial_console_reporter * console_reporter = new_financial_console_reporter();
        console_reporter->print(financial_report_result->result);
        free_financial_console_reporter(console_reporter);
    }

    free_financial_report_result(financial_report_result);
    free_financial_report_generator(financial_report_generator);

    return 0;
}

static report_type get_report_type_from_user() {
    char colored_output = '\0';
    do {
        printf("Colored output (Y/N)? ");
        scanf(" %c", &colored_output);
    } while (colored_output != 'Y' && colored_output != 'N');

    report_type report_type = colored_output == 'Y' ? COLORED : BLACK_WHITE;

    return report_type;
}
