#include "../inc/libmx.h"

void mx_delintarr(int ***IntArrArr) {
    for (int i = 0; (*IntArrArr)[i] != NULL; i++) {
        mx_intdel(&(*IntArrArr)[i]);
    }
    free(*IntArrArr);
    *IntArrArr = NULL;
}
