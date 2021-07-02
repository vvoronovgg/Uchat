#include "../inc/libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    int LengthOfNeedle = mx_strlen(needle);
    int LengthOfHaystack = mx_strlen(haystack);

    if (LengthOfHaystack < LengthOfNeedle)
        return NULL;
    char *buff = NULL;
    buff = mx_strnew(LengthOfNeedle);
    int Next;
    const char *Follower = haystack;

    for (int i = 0; i < LengthOfHaystack; i++) {
        Next = 0;
        for (int j = 0; j < LengthOfNeedle; j++) {
            if (haystack[i + Next] == '\0')
                return NULL;
            buff[j] = haystack[i + Next];
            Next++;
        }
        if (mx_strcmp(buff, needle) == 0) {
            free(buff);
            return (char *)Follower;
        }   
        Follower++;
    }
    free(buff);
    return NULL;
}

// int main() {
//     char haystack[] = "Bye Baby, bye!";
//     char needle[] = "Baby";
//     char *result = mx_strstr(haystack, needle);
//     printf("%s\n", result);
//     free(result);
//     printf("%s\n", haystack);
//     return 0;
// }
