#include "../inc/libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
    if (arr && delim && *arr)  {
        int ArrLength = 0;
        
        for (int i = 0; arr[i] != NULL; i++) {
            ArrLength++;
        }
        for (int i = 0; i < ArrLength; i++) {
            mx_printstr(arr[i]);
            if (i != ArrLength - 1)
                mx_printstr(delim);
        }
        mx_printchar('\n');
    }
}

// int main () {
//     char *arr[] = {"Great", "Awesome", "Fantastic", "OK", "Not a problem at all!", NULL, NULL, NULL, NULL};
//     const char *delim = "1";
//     mx_print_strarr(arr, delim);
//     printf("Finish!");
//     return 0;
// }

