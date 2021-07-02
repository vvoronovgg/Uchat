#include "../inc/libmx.h"

static void Check_Number_Or_Letter(int ElemOfArr, char *Dec_number) {
    if (ElemOfArr > 47 && ElemOfArr < 58) {
                *Dec_number = ElemOfArr - '0';
            }
            if (ElemOfArr > 64 && ElemOfArr < 71) {
                *Dec_number = ElemOfArr - '7';
            }
            if (ElemOfArr > 96 && ElemOfArr < 103) {
                *Dec_number = ElemOfArr - 'W';
            }
}

static double x_pow(int n, unsigned int pow) {
    double buffer = 1;

    for (unsigned int i = 0; i < pow; i++) {
        buffer *= n;
    }
    return buffer;
}

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long sum = 0;

    if (hex) {
        char number;

        int Length = mx_strlen(hex);
        int Down = Length - 1;
        for (int i = 0; i < Length; i++) {
            Check_Number_Or_Letter(hex[Down], &number);
            sum += number * x_pow(16, i);
            Down--;
        }
    }
    return sum;
}
