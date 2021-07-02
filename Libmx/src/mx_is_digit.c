#include "../inc/libmx.h"

bool mx_is_digit(char c) {
    return (c > 47 && c < 58) ? true : false;
}
