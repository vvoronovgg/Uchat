#include "../inc/libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    int i = 0;
    int LengthOfSrc = mx_strlen(src);

    if (LengthOfSrc >= len) {
        for (; i < len; i++) {
            dst[i] = src[i];
        }
        if (mx_strlen(dst) <= len)
            dst[i] = '\0';
    }
    else {
        for (; i < len; i++) {
            if (i > LengthOfSrc)
                dst[i] = '\0';
            else
                dst[i] = src[i];
        }
    }
    return dst;
}

// int main () {
//     char src[]="12345226789";
//     char dst[]= "1111111111";
//     printf("%s", mx_strncpy(dst, src, 2));
//     return 0;
// }
