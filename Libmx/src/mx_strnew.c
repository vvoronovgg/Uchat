#include "../inc/libmx.h"

char *mx_strnew(const int size) {
    char *OutputStr = NULL;

    if(size >= 0) {
        OutputStr = (char *) malloc ((size + 1) * sizeof(char));
        if (OutputStr) {
            for (int i = 0; i < size + 1; i++) {
                OutputStr[i] = '\0';
            }
        }
    }
    return OutputStr;
}
