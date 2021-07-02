#include "../inc/libmx.h"
#define MX_PRINT2DINTARR_NO_ARR "In function mx_print2dintarr: 'int **arr' doesn't exist"

void mx_print2d_sqrintarr(int **arr, char *title) {
    if (!arr) {
        mx_printstr(MX_PRINT2DINTARR_NO_ARR);
        exit(1);
    }
    int len = 0;
    for (int i = 0; arr[i] != NULL; i++, len++);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            mx_printstr(title);
            mx_printchar('[');
            mx_printint(i);
            mx_printchar(']');
            mx_printchar('[');
            mx_printint(j);
            mx_printchar(']');
            mx_printchar(' ');
            mx_printchar('=');
            mx_printchar(' ');
            mx_printint(arr[i][j]);
            mx_printchar('\n');
        }
    }
}
