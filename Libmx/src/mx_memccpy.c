#include "../inc/libmx.h"

static int get_char_indexn(const char *str, char c, int n) {
    if (!str)
        return -2;
    int counter = -1;
    
    for (int i = 0; i < n; i++) {
        if (str[i] == c)
            return i;
    }
    return counter;
}


void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    char *Dst = (char *)dst;
    const char *Src = (const char *)src;

    if (get_char_indexn(Src, c, n) == -1)
        return NULL;

    while (n--) {
        if (*Src == (char)c) {
            *Dst = *Src;
            return Dst;
        }
        *Dst++ = *Src++;
    }
    return Dst;
}

// int main() {
//     unsigned char src[] = "BHello, Baby, my Darling!";
//     char dst[6] = "";
//     mx_memccpy(dst, src, 'D', 20);
//     printf("%s", dst);
//     return 0;
// }
