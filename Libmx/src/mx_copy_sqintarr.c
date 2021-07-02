#include "../inc/libmx.h"

static void error_handling(int **src, int ***dest);

void mx_copy_sqintarr(int **src, int ***dest) {
    error_handling(src, dest);
    int len = 0;

    for (int i = 0; src[i] != NULL; i++, len++);
    *dest = mx_intarrnew(len);
    for (int i = 0; i < len; i++) {
        (*dest)[i] = mx_intnew(len);
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            (*dest)[i][j] = src[i][j];
        }
    }
}

#define COPY_SQRTINTARR_DEST_NOT_EMPTY "\nIn function mx_copy_sqrt_intarr: '*dest' must be empty (NULL)!\n"
#define COPY_SQRTINTARR_SRC_NOT_EXIST "\nIn function mx_copy_sqrt_intarr: 'int **src' must not be empty!\n"

static void error_handling(int **src, int ***dest) {
    if (*dest) {
        mx_print_chars('-', 60);
        mx_printchar('\n');
        mx_printstr(COPY_SQRTINTARR_DEST_NOT_EMPTY);
        mx_print_chars('-', 60);
        mx_printchar('\n');
        exit(1);
    }

    if (!src) {
        mx_print_chars('-', 60);
        mx_printchar('\n');
        mx_printstr(COPY_SQRTINTARR_SRC_NOT_EXIST);
        mx_print_chars('-', 60);
        mx_printchar('\n');
        exit(1);
    }
}

// int main () {
//     int **arr = mx_intarrnew(5);
//     for (int i = 0; i < 5; i++)
//         arr[i] = mx_intnew(5);
//     for (int j = 0; j < 5; j++) {
//         for (int i = 0; i < 5; i++) {
//             arr[j][i] = -4;
//         }
//     }
//     int **newarr = NULL;
//     mx_copy_sqrtintarr(arr, &newarr);
//     mx_print2d_sqrintarr(newarr, "newarr");
//     return 0;
// }
