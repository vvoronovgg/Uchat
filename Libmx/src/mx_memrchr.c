#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    unsigned char *str = (unsigned char *)s;
    unsigned int StrLen = (unsigned int)mx_strlen((char *)s);
    unsigned int End = 0;

    while (End != StrLen) {
        str++;
        End++;
    }
    while (n-- && StrLen-- ) {
        if (*str == (char)c)
            return str;
        str--;
    }
    return NULL;
}

// int main () {
//      printf("%s", (char *)mx_memrchr("Trinity", 'i', 7));
//      return 0;
// }
