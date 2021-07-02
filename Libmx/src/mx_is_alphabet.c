#include "../inc/libmx.h"

bool mx_is_alphabet(char c) {
    return ((c > 64 && c < 91) || (c > 96 && c < 123)) ? true : false;
}
