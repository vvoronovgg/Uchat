#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int k = 0;
    char *buf;

    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) { 
                k++;
                buf = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = buf;
            }
        }
    }
    return k;
}
