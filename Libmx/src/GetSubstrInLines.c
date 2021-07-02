#include "../inc/libmx.h"

char *GetSubstrInLines(char *substr, char **Lines, unsigned int StartLine) {
    if (StartLine > (unsigned)mx_strarrlen(Lines) || !Lines || !*Lines || !substr)
        return NULL;
    char *FoundSubStr = NULL;

    for (unsigned int i = StartLine; Lines[i] != NULL; i++) {
        FoundSubStr = mx_strstr(Lines[i], substr);
        if (FoundSubStr) {
            return FoundSubStr;
        }
    }
    return NULL;
}
