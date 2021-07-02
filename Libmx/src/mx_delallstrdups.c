#include "../inc/libmx.h"

static char **ReplaceDups(char **StrArr) {
    char **buffer = mx_strarrdup(StrArr);
    int FirstComp;
    int flag = 1;
    int StrArrLen = mx_strarrlen(buffer);

    for (int i = 0; i < StrArrLen; i++) {
        FirstComp = 1;
        while (flag) {
            if (i < StrArrLen && buffer[i][0] == '\0')
                i++;
            else flag = 0;
        }
        for (int j = i; j < StrArrLen; j++) {
            if (!FirstComp && mx_strcmp(buffer[i], buffer[j]) == 0) {
                mx_strdel(&buffer[j]);
                buffer[j] = mx_strnew(0);
            }
            else FirstComp = 0;
        }
        flag = 1;
    }
    return buffer;
}

char **mx_delallstrdups(char **StrArr) {
    if (!StrArr || !*StrArr)
        return NULL;
    char **buffer = ReplaceDups(StrArr);
    int NewStrArrLen = 0;

    for (int i = 0; buffer[i] != NULL; i++) {
        if (buffer[i][0] != '\0')
            NewStrArrLen++;
    }
    char **NewStrArr = mx_strarrnew(NewStrArrLen);
    int k = 0;

    for (int i = 0; k < NewStrArrLen; i++) {
        if (buffer[i][0] != '\0') {
            NewStrArr[k] = mx_strdup(buffer[i]);
            k++;
        }
    }
    mx_del_strarr(&buffer);
    return NewStrArr;
}
