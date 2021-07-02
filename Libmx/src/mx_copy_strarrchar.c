#include "../inc/libmx.h"

static char *cutstr(char *str, char stop) {
    int len = 0;

    for (int i = 0; str[i] != stop && str[i] != '\0'; i++, len++) {
    }
    char *newstr = mx_strnew(len);
    for (int i = 0; str[i] != stop && str[i] != '\0'; i++) {
        newstr[i] = str[i];

    }
    return newstr;
}

char **mx_copy_strarrchar(char **strarr, char stop) {
    if (!strarr || !*strarr)
        return NULL;
    
    int strarrlen = mx_strarrlen(strarr);
    
    char **newstrarr = mx_strarrnew(strarrlen);
    
    for (int i = 0; i < strarrlen; i++) {
        newstrarr[i] = cutstr(strarr[i], stop);
    }
    return newstrarr;
}

// int main() {
//     char **str = mx_strarrnew(4);
//     for (int i = 0; i < 4; i++) {
//         str[i] = mx_strdup("Kyiv-Lviv,1");
//     }
//     char **newstr = mx_copy_strarrchar(str, ',');
//     mx_print_strarr(newstr, " ");
//     mx_del_strarr(&str);
//     mx_del_strarr(&newstr);
//     system("leaks -q o");
// }
