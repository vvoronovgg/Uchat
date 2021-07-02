#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    char *Dst = (char *)dst;
    const char *Src = (char *)src;
    char *buff = mx_strnew(len);
    if (!buff)
        return NULL;

    for (unsigned int i = 0; i < len; i++)
        buff[i] = Src[i];
    for (unsigned int i = 0; i < len; i++)
        Dst[i] = buff[i];
    free(buff);
    return Dst;
}

// int main() {
//     char src[11] = "1234567890";
//     char dst[11] = "";
//     mx_memmove(dst, &src[3], 3);
//     printf("%s", dst);
//     return 0;
// }
