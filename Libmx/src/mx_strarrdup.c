#include "../inc/libmx.h"

char **mx_strarrdup(char **StrArr) {
    if (!StrArr || !*StrArr)
        return NULL;
    char **NewStrArr = NULL;
    int StrArrLen = mx_strarrlen(StrArr);
    NewStrArr = mx_strarrnew(StrArrLen);

    for (int i = 0; StrArr[i] != NULL; i++) 
        NewStrArr[i] = mx_strdup(StrArr[i]);
    return NewStrArr;
}
