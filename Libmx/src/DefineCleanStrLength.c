#include "../inc/libmx.h"

int DefineCleanStrLength(char *TrimmedStr) {
    if (!TrimmedStr)
        return -1;
    
    int CleanStrLength = 0;
    int i = 0;
    bool SearchFirstWspace = false;
    
    while (TrimmedStr[i] != '\0') {
        if (!mx_is_whitespace (TrimmedStr[i])) {
            CleanStrLength++;
            SearchFirstWspace = true;
        }
        if (mx_is_whitespace(TrimmedStr[i]) && SearchFirstWspace) {
            CleanStrLength++;
            SearchFirstWspace = false;
        }
        i++;  
    }
    return CleanStrLength;
}
