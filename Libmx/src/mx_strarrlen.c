#include "../inc/libmx.h"

int mx_strarrlen(char **StrArr) {
    if (!StrArr)
        return -1;
    int counter = 0;
    
    for (int i = 0; StrArr[i] != NULL; i++) {
        counter++;
    }
    return counter;
}
