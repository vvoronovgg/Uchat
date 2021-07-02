#include "../inc/libmx.h"

static void FillNewStrArr(char **StrArr, char ***NewStrings, char delim) {
    int WordsAmnt;
    char **tmp = NULL;
    int k = 0;

    for (int i = 0; StrArr[i] != NULL; i++) {
        WordsAmnt = mx_count_words(StrArr[i], delim);
        tmp = mx_strsplit(StrArr[i], delim);
        for (int j = 0; j < WordsAmnt; j++) {
            (*NewStrings)[k] = mx_strdup(tmp[j]);
            k++;
        }
        mx_del_strarr(&tmp);
    }
}

char **mx_strsplitall(char **StrArr, char delim) {
    if (!StrArr || !*StrArr)
        return NULL;
    int PiecesAmnt = 0;

    for (int i = 0; StrArr[i] != NULL; i++) {
        PiecesAmnt += mx_count_words(StrArr[i], delim);
    }
    char **NewStrings = mx_strarrnew(PiecesAmnt);
    if (!NewStrings)
        return NULL;
    FillNewStrArr(StrArr, &NewStrings, delim);
    return NewStrings;
}
