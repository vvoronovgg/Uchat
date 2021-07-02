#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
    if(!str)
        return NULL;
    int NewLength = 0;
    bool FoundLeftLetter, FoundRightLetter = false;
    int Right = mx_strlen(str) - 1;
    int Left = 0;
    
    while (Left < Right + 1 && !FoundLeftLetter) {
        if (!mx_is_whitespace(str[Left]))
            FoundLeftLetter = true;
        else Left++;
    }
    while (Right > -1 && !FoundRightLetter) {
        if (!mx_is_whitespace(str[Right]))
            FoundRightLetter = true;
        else Right--;
    }
    int LeftCopy = Left;

    while (Left <= Right) {
        NewLength++;
        Left++;
    }
    char *NewStr = NULL;
    NewStr = mx_strnew(NewLength);
    if (!NewStr)
        return NULL;
    int i = 0;

    while (LeftCopy <= Right) {
        NewStr[i] = str[LeftCopy];
        i++;
        LeftCopy++;
    }
    NewStr[i] = '\0';
    return NewStr;
}

// int main () {
//     printf("%s\n", mx_strtrim("\fMy name... is Neo\t\n"));
//     printf("%s\n", mx_strtrim("\n\t\f\r\n"));
//     printf("%s", mx_strtrim(NULL));
//     return 0;
// }
