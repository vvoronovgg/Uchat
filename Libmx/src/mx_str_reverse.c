#include "../inc/libmx.h"

void mx_str_reverse(char *s) {
    if (s) {
        int Right = mx_strlen(s) - 1;
        int Left = 0;
        while (Left <= Right) {
            mx_swap_char(&s[Left], &s[Right]);
            Left++;
            Right--;
        }
    }
}

// int main () {
//     char *a = "Bye";
//     mx_str_reverse(a);
//     printf ("a = %s", a);
//     return 0;
// }
