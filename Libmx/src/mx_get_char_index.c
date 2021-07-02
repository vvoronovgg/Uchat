#include "../inc/libmx.h"

int mx_get_char_index(const char *str, char c) {
    if (!str)
        return -2;
    int counter = -1;
    
    for (int i = 0; i < mx_strlen(str); i++) {
        if (str[i] == c)
            return i;
    }
    return counter;
}

// int main () {
//     char str[] = "AbcdEA";
//     printf("counter = %d\n", mx_get_char_index(str, 'A'));
//     return 0;
// }
