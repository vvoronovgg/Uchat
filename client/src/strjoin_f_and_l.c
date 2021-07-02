#include "client.h"

char *strjoin_f_and_l(char *f, char *l) {
    char *tmp = NULL;
    char *res = NULL;
    tmp = mx_strjoin(f, " ");
    res = mx_strjoin(tmp, l);
    return res; 
}
