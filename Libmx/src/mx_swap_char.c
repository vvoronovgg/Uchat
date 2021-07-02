#include "../inc/libmx.h"

void mx_swap_char(char *s1, char *s2) {
    if (s1 && s2) {
        char buf = *s1;
        *s1 = *s2;
        *s2 = buf;
    }
}

// int main () {
//     char str[] = "5 4 3 2 1 0";
//     mx_swap_char(&str[0], &str[1]);
//     printf("str = %s", str);
//     return 0;
// }
