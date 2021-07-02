#include "../inc/libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    char *Str = (char *)b;
    if (b)
        for (unsigned int i = 0; i < len; i++) {
            *Str = (char)c;
            Str++;
    }
    return Str;
}

// int main() {
//     //char str[] = "Hello, Baby, my Darling!";
//     char str1[100] = "";
//     mx_memset(NULL, 'x', 50);
//     printf("str = %s", str1);
//     return 0;
// }

