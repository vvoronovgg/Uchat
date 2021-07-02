#include "../inc/libmx.h"

int mx_getindex_foundstr(char *what, char **where, unsigned int begin_with) {
    for (int i = begin_with; where[i] != NULL; i++) {
        if (mx_strcmp(what, where[i]) == 0) {
            return i;
        }
    }
    return -1;
}
