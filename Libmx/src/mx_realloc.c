#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    char *NewPtr = malloc(size);
    if (!NewPtr)
        return NULL;
    if (!ptr)
        return NewPtr;
    if ((unsigned int)mx_strlen((char *)ptr) > size)
        mx_memcpy(NewPtr, ptr, size);
    else
        mx_memcpy(NewPtr, ptr, mx_strlen((char *)ptr));
    free(ptr);
    return NewPtr;
}

// int main() {
//     char *str = NULL;
//     str = mx_strnew(10);
//     mx_memset(str, 'a', 10);
//     str = (char *)mx_realloc(str, 20);
//     mx_memset(str, 'b', 19);
//     str[19] = '\0';
//     printf("%s", str);
//     free(str);
// }
