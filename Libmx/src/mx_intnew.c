#include "../inc/libmx.h"

int *mx_intnew(unsigned int size) {
    int *NewArr = NULL;
    NewArr = (int *)malloc(sizeof(int) * size);

    if (!NewArr)
        return NULL;
    for (unsigned int i = 0; i < size; i++) {
        NewArr[i] = 0;
    }
    return NewArr;
}
