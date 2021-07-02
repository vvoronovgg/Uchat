#include "../inc/libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    
    char *Dst = (char *)dst;
    const char *Src = (char *)src;
    char *buff = mx_strnew(n);
    if (!buff)
        return NULL;

    for (unsigned int i = 0; i < n; i++)
        buff[i] = Src[i];
    for (unsigned int i = 0; i < n; i++)
        Dst[i] = buff[i];
    free(buff);
    return Dst;
}

// int main() {
//     //char src[10] = "";
//     char dst[10] = "";
//     char src[10] = "123456789L";
//     //char dst[10] = "1234567890";
//     mx_memcpy(dst, src, 5);
//     printf("My: dst: %s\n", dst);
//     // memcpy(dst, src, 5);
//     // printf("Lib: dst: %s\n", dst);
//     return 0;
// }
