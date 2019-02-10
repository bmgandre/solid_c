#include "time_sheet.h"

struct time_record* pointer_to_time_record(gpointer const pointer) {
    return (struct time_record*) pointer;
}

gpointer time_record_to_pointer(struct time_record * const time_record) {
    return (gpointer) time_record;
}

static time_record_convert _time_record_convert = {
    .to_time_record = &pointer_to_time_record,
    .to_gpointer = &time_record_to_pointer
};

const time_record_convert * const time_record_converter = &_time_record_convert;
