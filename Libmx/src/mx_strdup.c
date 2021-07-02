#include "../inc/libmx.h"

char *mx_strdup(const char *str) {
    char *DupStr = mx_strnew(mx_strlen(str));

    if (!DupStr) 
        return NULL;
    mx_strcpy(DupStr, str);
    return DupStr;
}
