#include "../inc/libmx.h"

static void WriteErrFreeExit(char *error, char **StrArr) {
    write(2, error, mx_strlen(error));
    mx_del_strarr(&StrArr);
    exit(1);
}

static void validation(char **StrArr, unsigned int StartStr, int DelimedPart) {
    char *error = "\nIn function 'mx_shorten_strs_delim: Incorrect argument 'char **StrArr'\n";
    char *error1 = "\nIn function 'mx_shorten_strs_delim: Argument 'int DelimedPart' must be equal to 0 or 1\n";
    char *error2 = "\nIn function 'mx_shorten_strs_delim: Argument 'int StartStr' can't be more than string array length\n";

    if (!StrArr || !*StrArr) 
        WriteErrFreeExit(error, StrArr);
    if (DelimedPart != 0 && DelimedPart != 1) 
        WriteErrFreeExit(error1, StrArr);
    if (StartStr > (unsigned)mx_strarrlen(StrArr))
        WriteErrFreeExit(error2, StrArr);
}

char **mx_shorten_strs_delim(char **StrArr, char delim, unsigned int StartStr, unsigned int DelimedPart) {
    validation(StrArr, StartStr, DelimedPart);
    int StrArrLen = mx_strarrlen(StrArr);
    char **SepdStrs = NULL;
    char **ShortenStrs = mx_strarrnew(StrArrLen - StartStr);
    char *error = "In function mx_shorten_strs_delim: 'Unsuccessful malloc'";
    int k = 0;

    if (!ShortenStrs) {
        write(2, error, mx_strlen(error));
        mx_del_strarr(&StrArr);
        exit(1);
    }
    for (unsigned int i = StartStr; i < (unsigned)StrArrLen; i++) {
        SepdStrs = mx_strsplit(StrArr[i], delim);
        ShortenStrs[k] = mx_strdup(SepdStrs[DelimedPart]);
        mx_del_strarr(&SepdStrs);
        k++;
    }
    return ShortenStrs;
}
