#include "../inc/libmx.h"

int **mx_intarrnew(unsigned int size) {
    int **D2IntArr = (int **)malloc(sizeof(int *) * size + 8);

    if (!D2IntArr)
        return NULL;
    for (unsigned int i = 0; i < size + 1; i++) {
        D2IntArr[i] = NULL;
    }
    return D2IntArr;
}
