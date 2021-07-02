#include "../inc/libmx.h"

void mx_del_strarr(char ***arr) {
    if (!arr)  
        return;
    int counter = 0;
    int i = 0;

    while (**arr != NULL) {
        mx_strdel(&*arr[i]);  
        (*arr)++;
        counter++;
    }
    for (int i = 0; i < counter; i++) {
        (*arr)--;
    }
    free (*arr);
    *arr = NULL;
}

// int main() {
//     char **arr = NULL;
//     arr = (char**)malloc(3 * sizeof(char*));
//     for (int i = 0; i < 3; i++){
//         arr[i] = mx_strnew(3);
//     }
//     for (int i = 0; i < 2; i++){
//         for (int j = 0; j < 3; j++){
//             arr[i][j] = 'a';
//         }
//     }
//     arr[2] = NULL;
//     for (int i = 0; i < 3; i++) {
//             printf("arr[%d] = %s\n", i, arr[i]);
//     }
//     mx_del_strarr(&arr);
//     return 0;
// }
