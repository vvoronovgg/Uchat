#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    unsigned int StrLength = mx_strlen(s1);
    char *DupStr = mx_strnew(StrLength);

    if (!DupStr) 
        return NULL;
    if (StrLength <= n)
        DupStr = mx_strncpy(DupStr, s1, StrLength);
    else 
        DupStr = mx_strncpy(DupStr, s1, n);
    return DupStr;
}

// int main() {
//     char *Res = NULL;
//     Res = mx_strndup("Hello", 100);
//     printf("%s\n", Res);
//     free(Res);
// }

