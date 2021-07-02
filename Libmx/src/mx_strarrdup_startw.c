#include "../inc/libmx.h"

#define MX_STRARRDUP_STARTW_NOT_EMPTY "\nIn function 'mx_strarrdup_startw': '*(char ***dst)' must be empty!\n"
#define MX_STRARRDUP_STARTW_NOT_EXIST_SRC "\nIn function 'mx_strarrdup_startw': 'char **src' doesn't exist!\n"
#define MX_STRARRDUP_STARTW_NOT_EXIST_SSRC "\nIn function 'mx_strarrdup_startw': '*(char **src)' doesn't exist!\n"
#define MX_STRARRDUP_STARTW_LEN "\nIn function 'mx_strarrdup_startw': 'unsigned int startw' is more than src length!\n"


/*копирует массив строк, начиная с startw*/
void mx_strarrdup_startw(char **src, char ***dst, unsigned int startw) {
    if (!src)
        mx_print_error(MX_STRARRDUP_STARTW_NOT_EXIST_SRC);
    if (!*src)
        mx_print_error(MX_STRARRDUP_STARTW_NOT_EXIST_SSRC);
    if (*dst)
        mx_print_error(MX_STRARRDUP_STARTW_NOT_EMPTY);
    if (startw > (unsigned) mx_strarrlen(src))
        mx_print_error(MX_STRARRDUP_STARTW_LEN);

    unsigned int len = 0;
    int k = 0;

    for (unsigned int i = startw; src[i] != NULL; i++, len++); 
    
    *dst = mx_strarrnew(len);
    
    for (unsigned int i = startw; src[i] != NULL; i++) {
        (*dst)[k] = mx_strdup(src[i]);
        k++;
    }
}

// int main(int argc, char **argv) {
//     char **res = NULL;
//     mx_strarrdup_startw(argv, &res, 4);
//     mx_print_strarr(res, " ");
//     argc = 1;
// }

//clang -std=c11 -Wall -Werror -Wpedantic -Wextra -o o Libmx/src/*.c -I Libmx/inc
