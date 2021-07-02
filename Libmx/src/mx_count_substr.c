#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    if (!str || !sub)
        return -1;
    int LengthOfSub = mx_strlen(sub);
    int LengthOfStr = mx_strlen(str);

    if (LengthOfStr < LengthOfSub || *sub == '\0')
        return 0;
    char *buff = NULL;
    buff = mx_strnew(LengthOfSub);
    int Next;
    int counter = 0;

    for (int i = 0; i < LengthOfStr; i++) {
        Next = 0;
        for (int j = 0; j < LengthOfSub; j++) {
            if (str[i + Next] == '\0')
                return counter;
            buff[j] = str[i + Next];
            Next++;
        }
        if (mx_strcmp(buff, sub) == 0) 
            counter++;
    }
    free(buff);
    return counter;
}

// int main() {
//     const char *str = "yo, yo, yo Neo";
//     const char *sub = "";
    
//     printf("%d\n", mx_count_substr(str, sub));
//     printf("%d\n", mx_count_substr(NULL, NULL));
//     return 0;
// }
