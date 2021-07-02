#include "../inc/libmx.h"

void mx_intdel(int **int_array) {
    free(*int_array);
    *int_array = NULL;
}
