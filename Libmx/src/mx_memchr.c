#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char *str = (unsigned char *)s;

    while (n-- && *str != '\0') {
        if (*str == (char)c)
            return str;
        str++;
    }
    return NULL;
}

// int main () {

//     printf("%s", (char *)mx_memchr("", 33, 10));
//     return 0;
// }
