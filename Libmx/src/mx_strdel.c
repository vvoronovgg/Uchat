#include "../inc/libmx.h"

void mx_strdel(char **str) {
    free(*str);
    *str = NULL;
}

// int main () {
//     char *str = NULL;
//     str = mx_strnew(10);
//     printf("str = %s", str);
//     return 0;
// }
