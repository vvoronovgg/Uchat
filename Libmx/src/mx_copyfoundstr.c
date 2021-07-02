#include "../inc/libmx.h"

char *mx_copyfoundstr(char *what, char **where, unsigned int begin_with) {
    char *FoundStr = NULL;

    for (int i = begin_with; where[i] != NULL; i++) {
        if (mx_strcmp(what, where[i]) == 0) {
            FoundStr = mx_strdup(where[i]);
            return FoundStr;
        }
    }
    return NULL;
}
