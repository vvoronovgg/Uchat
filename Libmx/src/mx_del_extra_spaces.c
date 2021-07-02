#include "../inc/libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (!str) {
        return NULL;
    }
    char *TrimmedStr, *CleanStr = NULL;
    
    TrimmedStr = mx_strtrim(str);
    int CleanStrLength = DefineCleanStrLength(TrimmedStr); 
    CleanStr = mx_strnew(CleanStrLength);
    if (!CleanStr)
        return NULL;
    CleanStr = DelimWords(CleanStr, TrimmedStr, ' ');
    free(TrimmedStr);
    return CleanStr;
}

// int main() {
//     char *res = mx_del_extra_spaces("\\f  My name... is Neo  \\t\\n");
//     printf("%s\n", res);
//     printf("%d\n", mx_strlen(res));
//     return 0;
// }
