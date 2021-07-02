#include "../inc/libmx.h"

void mx_print_error(const char *s) {
    write(2, s, mx_strlen(s));
    write(2, "\n", 1);
    exit(1);
}
