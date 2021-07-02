#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    unsigned char *str1 = (unsigned char *)s1;
    unsigned char *str2 = (unsigned char *)s2;

    while(n-- && *str1 != '\0' && *str1 == *str2) {
        if (n == 0)
            return *str1 - *str2;
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// int main () {
//     char big[] = "H1llo, nice to meet you again!";
//     char little[] = "He";

//     printf("%d", mx_memcmp(big, little, 1));
//     return 0;
// }
