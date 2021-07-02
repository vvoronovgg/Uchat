#include "../inc/libmx.h"

bool mx_is_whitespace(char c) {
    return (c == '\n' || c == '\t' || c == '\v' || c == '\f' ||
        c == '\r' || c == ' ') ? true : false;
}
