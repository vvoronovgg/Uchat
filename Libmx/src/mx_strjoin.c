#include "../inc/libmx.h"

static char *NewStrCopy (const char *str) {
    char *NewCopy = NULL;
    NewCopy = mx_strdup(str);
    return NewCopy;
}

char *mx_strjoin(const char *s1, const char *s2) {
    if (!s1 && !s2) 
        return NULL;
    if (*s1 == '\0' && *s2 == '\0') 
        return mx_strnew(0);
    if (!s1 || *s1 == '\0') 
        return NewStrCopy(s2);
    if (!s2 || *s2 == '\0') 
        return NewStrCopy(s1);

    int S1Len = mx_strlen(s1);
    int S2Len = mx_strlen(s2);
    char *JoinedStr = NULL;

    JoinedStr = mx_strnew(S1Len + S2Len);
    if (!JoinedStr) 
        return NULL;
    for (int i = 0; i < S1Len + S2Len; i++) {
        if (i < S1Len)
            JoinedStr[i] = s1[i];
        else
            JoinedStr[i] = s2[i - S1Len];
    }
    return JoinedStr;
}

// int main () {
//     char *OutputStr = mx_strjoin("-", "Kyiv-Kharkiv,2");
//     printf("%s", OutputStr);
//     char *Rely = mx_strjoin("-", "Kyiv-Kharkiv,2");
//     system("leaks -q o");
//     free(OutputStr);
//     free(Rely);
//     return 0;
// }
