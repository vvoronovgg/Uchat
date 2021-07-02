#include "../inc/libmx.h"

int FindLeftLetterIndex(char *str) {
    if (!str)
        return -2;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!mx_is_whitespace(str[i]))
            return i;
    }
    return -1;       
}
