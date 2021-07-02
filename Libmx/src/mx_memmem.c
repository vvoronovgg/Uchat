#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, 
                size_t little_len) {
    if (little_len > big_len || little_len == 0 || big_len == 0)
        return NULL;
    const unsigned char *Haystack = (const unsigned char*)big;
    const unsigned char *Needle = (const unsigned char*)little;

        while (*Haystack != '\0') {
            if (mx_memcmp(Haystack, Needle, little_len) == 0)
                return (unsigned char*)Haystack;
            Haystack++;
        }
        return NULL;
}

// int main () {
//     char big[] = "Hello, nice to meet you again!";
//     char little[] = "Hello, nice to meet you again!";
//     printf("%s", (char *)mx_memmem(big, 30, little, 1));
//     return 0;
// }
