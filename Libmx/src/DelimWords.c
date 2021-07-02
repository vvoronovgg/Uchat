#include "../inc/libmx.h"

char *DelimWords(char *dest, char *TrimdStr, char delim) {
    if (!dest || !TrimdStr)
        return NULL;
    bool isWSpace;
    int AmountWsp = 0;
    int i = 0;
    int Prev = 0;

    while (TrimdStr[i] != '\0') {
        isWSpace = mx_is_whitespace(TrimdStr[i]);
        if (isWSpace && AmountWsp == 0) {
            dest[i - Prev] = delim;
            AmountWsp++;
        }
        else if (isWSpace && AmountWsp > 0) 
            Prev++;
        else if (!isWSpace) {
            dest[i - Prev] = TrimdStr[i];
            AmountWsp = 0;
        }        
        i++;
    }
    return dest;
}
