#include "../inc/libmx.h"

char **mx_strarrnew(unsigned int StrAmnt) {
    char **StrArr = (char **)malloc(sizeof(char *) * StrAmnt + 1);
    
    if (!StrArr)
        return NULL;
    for (unsigned int i = 0; i < StrAmnt + 1; i++)
        StrArr[i] = NULL;
    return StrArr;
}
