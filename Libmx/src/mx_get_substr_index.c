#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    if (!str || !sub)
        return -2;
    int LengthOfSub = mx_strlen(sub);
    int LengthOfStr = mx_strlen(str);

    if (LengthOfStr < LengthOfSub)
        return -1;
    char *buff = NULL;
    buff = mx_strnew(LengthOfSub);
    if (!buff) return -1;
    int Next;

    for (int i = 0; i < LengthOfStr; i++) {
        Next = 0;
        for (int j = 0; j < LengthOfSub; j++) {
            if (str[i + Next] == '\0')
                return -1;
            buff[j] = str[i + Next];
            Next++;
        }
        if (mx_strcmp(buff, sub) == 0) {
            free(buff);
            return i;
        }   
    }
    free(buff);
    return -1;
}

// int main() {
//     char *haystack = NULL;
//     const char *needle = "Grrrr";
//     printf("%d", mx_get_substr_index(haystack, needle));
//     return 0;
// }
