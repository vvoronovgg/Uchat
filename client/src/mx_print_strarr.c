#include "client.h"

void mx_print_strarr(char **arr, const char *delim) {
    if (arr && delim && *arr)  {
        int ArrLength = 0;
        
        for (int i = 0; arr[i] != NULL; i++) {
            ArrLength++;
        }
        for (int i = 0; i < ArrLength; i++) {
            printf("%s\n", arr[i]);
            if (i != ArrLength - 1)
                printf("%s\n", delim);
        }
        printf("\n");
    }
}
